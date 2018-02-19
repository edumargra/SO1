#for D in */
llista=($(ls -S *.txt))
len=$((${#llista[*]} - 1))
if [ $len -ge 0 ]
then
	tail -n 2 ${llista[0]} 
	cat ${llista[0]} > tmp.txt
	tail -n 2 tmp.txt
	cat ${llista[$len]} > ${llista[0]}
	tail -n 2 ${llista[0]} 	
	tail -n 2 ${llista[$len]}
	cat tmp.txt > ${llista[$len]}
	rm -f tmp.txt
	tail -n 2 ${llista[$len]}
fi
