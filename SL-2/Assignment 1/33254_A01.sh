#!/bin/sh

menu() {
	echo
	echo "*******HOSPITAL MENU*******"
	echo "1) Add a Patient"
	echo "2) View all Patients"
	echo "3) Modify a Patient"
	echo "4) Delete a Patient"
	echo "5) Search for a Patient"
	echo "6) Exit"
	echo "---------------------------"
	echo "Enter your choice :"
	read option
}

create() {
	echo
	echo "Enter the name of the file to be worked on :"
	read filename
	echo
	
	if [ -f $filename ]
	then
		echo "File found!"
	else
		echo "File does not exist. Do you want to create it? (Y/N)"
		read choice
		
		case $choice in
		Y)
		touch $filename
		echo
		echo "New file created!" ;;
		*)
		create ;;
		esac
	fi
}

insert() {
	echo
	echo "Enter patient ID :"
	read ID
	echo "Enter name of the patient :"
	read name
	echo "Enter age of the patient:"
	read age
	echo "Enter disease/disorder :"
	read disease
	
	if [ -f $filename ]
	then
		echo "$ID\t $name\t $age\t $disease" >> "$filename"
		echo
		echo "Patient added successfully!"
	else
		echo "File not found!"
	fi
}

viewall() {
	echo
	echo "                     HOSPITAL DATABASE                          "
	echo "----------------------------------------------------------------"
	echo "ID\t Name\t\t\t Age\t Disease"
	echo "----------------------------------------------------------------"
	cat $filename
	echo "----------------------------------------------------------------"
}



modify() {
	echo
	echo "Enter the keyword to modify the record :"
	read keyword
	echo
	echo "----------------------------------------------------------------"
	
	if cat $filename | grep -i $keyword  
	then
		echo "----------------------------------------------------------------"
		l=$( cat $filename | grep -i $keyword )

		i=0
		for addr in $l
		do
			i=$((i+1))
			if [ $i -eq 1 ]
			then 
				newID=$addr
			fi
			
			if [ $i -eq 2 ]
			then 
				newname1=$addr
			fi
			
			if [ $i -eq 3 ]
			then 
				newname2=$addr
			fi
		done
		
		touch temp.txt
		echo
		echo "Ready to modify...."
		
		echo
		echo "Enter updated age :"
		read newage
		echo
		echo "Enter updated disease/disorder :"
		read newdisease
		
		echo "----------------------------------------------------------------"		
		while read p;
		do
			if echo $p | grep -i $keyword 
			then
				echo "$newID\t $newname1 $newname2\t $newage\t $newdisease" >> temp.txt
				echo "----------------------------------------------------------------"
			else
				echo "$p" >> temp.txt
			fi
		done < $filename
		
		rm $filename
		mv temp.txt $filename
		echo
		echo "Record(s) modifed successfully!"
	else
		echo "Record not found."
	fi
}

delete() {
	echo
	echo "Enter the keyword to delete the record :"
	read keyword
	echo
	
	if cat $filename | grep -i $keyword  
	then
		
		touch temp.txt
		echo "----------------------------------------------------------------"
		echo
		echo "Ready to delete...."
		echo
		
		while read p;
		do
			if echo $p | grep -i $keyword 
			then
				echo
				echo "Deleting......"
			else
				echo "$p" >> temp.txt
			fi
		done < $filename
		
		rm $filename
		mv temp.txt $filename
		echo
		echo "Record(s) deleted successfully!"
	else
		echo "Record not found."
	fi
}

search() {
	echo
	echo "Enter the keyword to be searched :"
	read keyword
	echo
	echo "----------------------------------------------------------------"
	
	if cat $filename | grep -i $keyword 
	then
		echo "----------------------------------------------------------------"
		echo "Record(s) found!"
	else
		echo "Sorry! Patient not found."
	fi
}

clear
create

while [ 1 ] 
do
	menu
	case $option in
	1)
	insert ;;
	2)
	viewall ;;
	3)
	modify ;;
	4)
	delete ;;
	5)
	search ;;
	6)
	break ;;
	*)
	echo "Wrong choice" ;;
	esac
done

