
#include "../header.h"

int epollfd;

typedef struct Node
{
    struct Node* next;
    struct Node* prev;
    int fd;
} Node;

typedef struct List
{
    Node head; 
} List;

List* list;
pthread_mutex_t mutex;
pthread_cond_t cond;

void addNode(Node* prev, Node* next, Node* node)
{
    prev->next = node;
    node->prev = prev;

    node->next = next;
    next->prev = node;
}

void delNode(Node* prev, Node* next)
{
    prev->next = next;
    next->prev = prev;
}

void addSockToQueue(int fd)
{
    Node* node = malloc(sizeof(Node));
    node->fd = fd;

    addNode(list->head.prev, &list->head, node);
}


int emptyList()
{
    if(list->head.next == &list->head) return 1;
    return 0;
}

int removeFirst()
{
    Node* node = list->head.next;
    int ret = node->fd;
    delNode(node->prev, node->next);
    free(node);
    return ret;
}

int total_count = 0;
int recv_data(int fd)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int ret = read(fd, buf, sizeof(buf));
    if(ret > 0)
    {
        total_count ++;
//        printf("%s\n", buf);
        return 0;
    }
    return -1;
}

void* thread_func(void* ptr)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        if(emptyList())
        {
            pthread_mutex_unlock(&mutex);
            continue;
        }
        int fd = removeFirst();
        pthread_mutex_unlock(&mutex);


        if(recv_data(fd) == 0)
            addEpoll(epollfd, fd, EPOLLIN|EPOLLONESHOT);
        else
            close(fd);
    }
}

void sighandle(int v)
{
    printf("%d\n", total_count);
    exit(0);
}

int main()
{
    signal(SIGINT, sighandle);
    int server = startTcpServer(9998, "0.0.0.0", 5);
    set_nonblock(server);

    // 创建线程
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    list = malloc(sizeof(List));
    list->head.prev = list->head.next = &list->head;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    epollfd = epoll_create(1024);
    addEpoll(epollfd, server, EPOLLIN);

    struct epoll_event ev[8];
    while(1)
    {
        // 8号文件描述符，有数据可读
        int count = epoll_wait(epollfd, ev, 8, 5000);

        if(count == 0 || errno == EINTR)
            continue;

        if(count < 0)
        {
            printf("epoll error\n");
            return 0;
        }

        int i;
        for(i=0; i<count; ++i)
        {
            int fd = ev[i].data.fd;
            if(fd == server)
            {
                while(1)
                {
                    int sock = accept(server, NULL, NULL);
                    if(sock == -1)
                    {
                        if(errno == EAGAIN) break;
                        return 0; // 如果真的有错误，那么服务器退出
                    }
                    set_nonblock(sock);
                    addEpoll(epollfd, sock, EPOLLIN | EPOLLONESHOT);
                }
            }
            else
            {
                // 把8号文件描述符放入队列
                pthread_mutex_lock(&mutex);
                addSockToQueue(fd);
                pthread_mutex_unlock(&mutex);
                pthread_cond_signal(&cond);
            }
        }
    }
}
