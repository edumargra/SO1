if [ $# == 3 ]
then
	for f in $(ls $1)
	do
        extensio=${f##*.}
        if [ $extensio == $2 ]
        then
            for word in $(cat $1/$f)
            do
                if [ $3 == $word ]
                then
                    echo $1/$f
                    break
                fi
            done
        elif [ -d $1/$f ]
        then
            ./ex5.sh $1/$f $2 $3
        fi
	done
	exit 0
else
	echo "ERROR: Introdueix tres parametres: un directori, una extensio i una cadena."
	exit 1
fi
