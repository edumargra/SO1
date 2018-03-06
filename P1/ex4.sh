if [ $# == 2 ]
then
	directory=$1
	numero=$2
	mkdir -p petits
	mkdir -p grans	
	ls -l $1 > info.txt
	mida=($(awk '{print $5}' info.txt))
	nom=($(awk '{print $9}' info.txt))
	rm info.txt
	for (( i = 0; i < ${#nom[*]}; i++ ))
	do
		if [ ! -d $1/${nom[$i]} ] 
		then
			if [  ${mida[$i]} -gt $numero ]
			then
				cp $1/${nom[$i]} grans
			else
				cp $1/${nom[$i]} petits
			fi
		fi
	done
else
	"ERROR: Introdueix dos paràmetres, un directori i una cadena"
fi									 
