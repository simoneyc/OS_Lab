GuessNumber(){
	echo "Enter the target number between 1 and 10"
	read target

	max=10
	min=1

	while true; do
	    echo "enter the target number:"
	    read guess

	    if [ $guess -eq $target ]; then
		echo "Bingo!"
		break
	    elif [ $guess -lt $target ]; then
	    	if [ $guess -lt $min ]; then
	    		echo "Please enter a number between $min and $max:"
	    		continue
	    	else
			min=$guess
			echo "Please enter a number between $min and $max:"
	   	fi 
	    else
	    	if [ $guess -gt $max ]; then
	    		echo "Please enter a number between $min and $max:"
	    		continue
	    	else
			max=$guess
			echo "Please enter a number between $min and $max:"
	 	fi   
	    fi
	done
}

GuessNumber;
