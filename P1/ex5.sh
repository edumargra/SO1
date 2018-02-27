if [ $# == 3 ]
then
	string=$3
	for f in $(ls $1)
	do
		echo $f
		if [ -d $f ]
		then 
			echo "a"
			echo $1/$f
			./ex4.sh $1/$f $2 $3
		elif [ ${f: -4} == ".$2" ]
		then
			for word in $(cat $1/$f)
			do
				if [ $string == word ]
				then
					echo $1
					break
				fi
			done
		else
			echo "b"
		fi
	done
	exit 0
else
	echo "ERROR: Introdueix tres parametres, un directori, una extensio i una cadena."
	exit 1
fi