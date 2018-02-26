if [ $# == 1 ]
then
	cd $1
	suma=0
	ls -l *.txt > info.txt
	for i in $(awk '{print $5}' info.txt)
	do
		suma=$(expr $suma + $i)
	done
	echo $suma
	exit 0
else
	echo "ERROR: Introdueix un unic parametre, un directori."
	exit 1
fi