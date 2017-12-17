root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
EOF

while read line
do
    for optX in 1
    do
	for optY in 4 
	do
	    root -l -b -q 'unfoldPtMass.cxx+('$optX','$optY',"'$line'")'
	done
    done
done < list.txt
