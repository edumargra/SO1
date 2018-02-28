if [ $# == 1 ]
then
	suma=0
	ls -l $1 > info.txt
	nom=($(awk '{print $9}' info.txt))
	mida=($(awk '{print $5}' info.txt))
	rm info.txt
	for (( i = 0; i < ${#nom[*]} ; i++ ))
	do
		if [ ! -d "${nom[$i]}" ]
		then
			suma=$(expr $suma + ${mida[$i]})
		fi
	done
	echo $suma
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi
