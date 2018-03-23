if [ $# == 1 ]
then
	suma=0
	suma=$(ls -lp $1 | grep -v / | awk '{suma += $5} END {print suma}')
	echo $suma $1
	find $1 -type d -exec ./ex2.sh {} \;
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi
