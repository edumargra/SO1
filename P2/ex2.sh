if [ $# == 1 ]
then
	suma=0
	suma=$(ls -lp $1 | grep -v / | awk '{suma += $5} END {print suma}')
	echo $suma $1
	for f in $(ls $1)	
	do
	if [ -d $1/$f ]
        then
            ./ex2.sh $1/$f
        fi
	done
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi
