class Shell {
				class Command {
								public:
								int argc;
								string *args;
								string name;
												Command() {
																argc = 0;
																args = NULL;
																name = "none";
												}
												Command(string name) : Command() {
																this->name = name;
												}
								};
				Command *comm;
				int size;
				public:
								Shell() {
												size = 0;
								}
								void addCommand(string name) {
												comm[size-1] = new Command(name);
												size++;
								}
};