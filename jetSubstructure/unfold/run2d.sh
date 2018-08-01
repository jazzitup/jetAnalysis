root -l <<EOF
gSystem->Load("libRooUnfold");
.L makeUnfMatrix2D.cxx++
EOF

optX=1
optY=2
doReweight=1
for kSample in 1 0 # 0 = pp,  1 = pbpb
do
    for etaBin in 0 1 2
    do
	root -l -b -q  'makeUnfMatrix2D.cxx+('$kSample','$optX','$optY','$etaBin','$doReweight')'
    done
done


