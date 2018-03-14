if [ $# == 1 ]
then
	suma=0
	mida=($(ls -f -l $1 | awk '{print $5}'))
	for (( i = 0; i < ${#mida[*]} ; i++ ))
	do
        suma=$(expr $suma + ${mida[$i]})
	done
	echo $suma $1
	nom=($(ls $1))
    for (( i = 0; i < ${#nom[*]} ; i++ ))
	do
        echo ${nom[$i]}
        if [ -d ${nom[$i]} ]
		then
			echo ${nom[$i]}
		fi
	done
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi
