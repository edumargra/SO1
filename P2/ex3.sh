if [ $# == 2 ]
then
    find $1 -type f -exec ls {} \; > files1.txt #exec
    find $2 -type f -exec ls {} \; | sed "s:$2:$1:g" > files2.txt
	for file1 in $(cat files1.txt)
	do
    	if ! grep -Fxq $file1 files2.txt
    	then
    		echo $file1
    	fi
    done
	exit 0
else
	echo "ERROR: Introdueix dos parametres: dos directoris."
	exit 1
fi
