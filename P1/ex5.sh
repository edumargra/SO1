if [ $# == 3 ]
then
	for f in $(ls $1/*.$2)
	do
		for word in $(cat $f)
		do
			if [ $3 == $word ]
			then
				echo $1/$f
				break
			fi
		done
	done
	for dir in $(ls $1/)
	do
		./ex5.sh $1/$dir $2 $3
	done
	exit 0
else
	echo "ERROR: Introdueix tres parametres: un directori, una extensio i una cadena."
	exit 1
fi
