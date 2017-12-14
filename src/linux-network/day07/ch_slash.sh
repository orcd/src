
files=`find test -name "*.c" -o -name "*.h"`

# \\\\\\\\ 字符串转义==> \\\\ 正则表达式转义==> \\

handle_file()
{
    filename=$1
    cp ${filename}_bak ${filename}
    cp $filename ${filename}_bak
    awk '/#include/{gsub("\\\\\\\\", "/") ;print $0} !/#include/{print $0}' $filename > ${filename}_r
    cp ${filename}_r ${filename}
}

for file in $files
do
    handle_file $file
done

