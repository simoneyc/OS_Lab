echo "Input the start number: "

read start

echo "Input the end number: "

read end

echo " "



now=0

flag=0

p=1

for ((now=start; now<=end; now++)); do



	for ((i=2; i<now; i++)); do

		flag=`expr $now % $i`

		if [ $flag -ne 0 ]; then

			continue

		else

			p=0

			break

		fi

	done

	

	if [ $p -eq 1 ]; then

		echo $now

	fi

	

	p=1

	

done

			

	