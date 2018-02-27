if [ $# == 2 ]
then
	cd $1
	pattern=$2
	len=${#pattern}
	for f in $(ls *.txt)
	do
		for word in $(cat $f)
		do
			if [ $pattern == "${word:0:len}" ]
			then
				echo "$f: $word"
			fi
		done
	done
	exit 0
else
	echo "ERROR: Introdueix dos parametres, un directori i una cadena."
	exit 1
fi