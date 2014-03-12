#include "JobQueueWidgets.h"

JobSelectorWidget *JobQueueWidgets::createJobSelectorWidget(QWidget *parent)
{
    return new JobSelectorWidget(parent);
}

JobPropertiesWidget *JobQueueWidgets::createJobPropertiesWidget(QWidget *parent)
{
    return new JobPropertiesWidget(parent);
}

JobOutputDataWidget *JobQueueWidgets::createJobOutputDataWidget(QWidget *parent)
{
    return new JobOutputDataWidget(parent);
}

