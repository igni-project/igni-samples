#include "main.h"

#include "cmd/cmdline.h"
#include "load_model.h"

int main(int argc, char *argv[])
{
	struct gengetopt_args_info args_info;

	cmdline_parser(argc, argv, &args_info);

	switch (args_info.sample_arg[0])
	{
	case 'l':
		return load_model();
	default:
		return 0;
	}
}

