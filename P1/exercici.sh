cd $1
llista=($(ls -S *.txt))
len=$((${#llista[*]} - 1))
if [ $len -ge 0 ]
then 
	cat ${llista[0]} > tmp.txt
	cat ${llista[$len]} > ${llista[0]} 
	cat tmp.txt > ${llista[$len]}
	rm -f tmp.txt
fi
