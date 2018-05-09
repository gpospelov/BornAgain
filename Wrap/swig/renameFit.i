// renaming should be done in advance and has to be placed at the start of the interface file

%rename(test_callback_cpp) Fit::Minimizer::test_callback;
%rename(minimize_cpp) Fit::Minimizer::minimize;
