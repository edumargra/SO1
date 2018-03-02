if [ $# == 3 ]
then
	for f in $(ls $1)
	do
        extensio=${f##*.}
        if [ $extensio == $2 ]
        then
            text=($(cat $1/$f))
            len=${#text[*]}
            i=0
            trobat=false
            while [ $trobat == false ] && [ $i -lt $len ]
            do
                if [ $3 == ${text[$i]} ]
                then
                    echo $1$f
                    trobat=true
                fi
                (( i++ ))
            done
        elif [ -d $1$f ]
        then
            ./ex5.sh $1$f $2 $3
        fi
	done
	exit 0
else
	echo "ERROR: Introdueix tres parametres: un directori, una extensio i una cadena."
	exit 1
fi
