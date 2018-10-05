// renaming should be done in advance and has to be placed at the start of the interface file

%rename(minimize_cpp) Fit::Minimizer::minimize;
%rename(add_cpp) Fit::Parameters::add;
