if [ $# == 1 ]
then
	suma=0
	suma=$(ls -l $1 | awk '{suma += $5} END {print suma}')
	echo $suma $1
	find . -type d -exec $1/ex2.sh {} \;
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi
