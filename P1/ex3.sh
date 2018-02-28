if [ $# == 2 ]
then
	pattern=$2
	len=${#pattern}
	for f in $(ls $1)
	do	
		if [ ! -d $f ]
		then
			for word in $(cat $f)
			do
				if [ $pattern == "${word:0:len}" ]
				then
					echo "$f: $word"
				fi
			done
		fi
	done
	exit 0
else
	echo "ERROR: Introdueix dos parametres, un directori i una cadena."
	exit 1
fi
