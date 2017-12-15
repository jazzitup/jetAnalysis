root -l <<EOF
gSystem->Load("libRooUnfold");
.L unfoldPtMass.cxx+
unfoldPtMass()
EOF