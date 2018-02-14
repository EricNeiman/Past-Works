/* start of the program
Eric Neiman
CMSC 257
Assignment 4
Shell Program
++ is a completed item
exit status of 0 is successful for children
*/

// c libraries
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

// defined sizes
#define shell_buffer 50
#define shell_delim " \t\r\n\a"

// shell function basic implementations	++					-----------------------------------------------------------------------------------------------
int shell_pid();
int shell_ppid();
int shell_cd(char **args);
int shell_help(char **args);
void shell_exit(char **args);

// universal variables and arrays ++
char *string_functions[]={"pid", "ppid", "cd", "help", "exit"}; // array of the strings for each command cd, help, exit, pid, ppid ++
int (*basic_functions[])(char **)={&shell_pid, &shell_ppid, &shell_cd, &shell_help, &shell_exit}; // array of the functions for each command, handles chdir/cwd, help, exit, pid, ppid ++


int shell_array_elements(){ return sizeof(string_functions)/sizeof(char *);} // number of elements in arrays and changes based off the number of elements in string_functions ++

int sig_handler(int sig){ // singnal handler method straight from the lab ++
	if(sig==SIGHUP){ // exits the shell
		return 0;
	}else if(sig==SIGINT){
		printf("\nThe shell cannot be closed by a signal interuption, only by the \"exit\" command.\n"); // handles SIGINT
		return 1;
	}
}

// shell function full implementaions 						-----------------------------------------------------------------------------------------------
int shell_pid(){ // getpid implementations	++																						getpid()
	pid_t pid=getpid();
	printf("child's Process ID: %d\n",pid);
	return 1; // returns a 1 so that the loop continues
}

int shell_ppid(){ // getpid implementations	++																						getpid()
	pid_t pid=getppid();
	printf("parent's Process ID: %d\n",pid);
	return 1; // returns a 1 so that the loop continues
}

int shell_cd(char **args){ // Change Directory, takes a list of arguments as long as the first one is "cd" ++						chdir() & getcwd()
	char *ptr;
	if(args[1]==NULL){ // just "cd" should print the current directory
		if(getcwd(*args, 1024)!=0){ // gets current working directory													
			ptr=getcwd(*args, 1024);
			fprintf(stdout, "%s\n", ptr); // prints out the working directory
		}else{perror(" cwd error");}
	}else{
		if(chdir(args[1])!=0){perror(" cd error");}	// changes directories											
	}
	return 1; // returns a 1 so that the loop continues
}

int shell_help(char **args){ // Help Command, takes "help" as the only argument ++
	int i;
	printf("Eric Neiman's Shell CMSC257\nAssingnment 4\nBuilt in functions:\n");
	for(i=0; i<shell_array_elements(); i++) {
		printf(" -> %s\n", string_functions[i]);
	}
	printf("The input limit is 50 characters.\nType exit to leave the shell.\n");
	return 1; // returns a 1 so that the loop continues
}

void shell_exit(char **args){ int i = raise(SIGHUP);} // method to exit the shell which loops until a 0 is returned ++				exit()

int shell_launch(char **args){ // launches the shell and waits until exit is called	++												execvp()
		if(execvp(args[0], args)==-1){ // runs non built in functions									
			perror(" execute error");
			exit(1);
		}else{
			execvp(args[0], args); // executes non implemented commands
		}
	return 1; // returns a 1 so that the loop continues
}

int shell_execute(char **args){ // checks to see if there were any input arguments and then determines which function to run ++		fork()
	pid_t pid;
	int i, status; // int for parsing arguments
	if(args[0]==NULL){ // no input argument case
		printf("Type \"help\" for a list of commands.\n");
		return 1; // returns a 1 so that the loop continues
	}				
	for(i=0; i<shell_array_elements(); i++){
		if (strcmp(args[0], string_functions[i])==0){
			return (*basic_functions[i])(args);
		}
	}	
	pid=fork();	// creates each child 											
	if(pid<0){
		perror(" fork failed\n");
			exit(1);
	}else if(pid>0){ // parent
		wait(&status);
		printf("Child exited with status: %d\n",WEXITSTATUS(status));
		//printf("new parent: with process ID: %d\n", getpid()); 
	}else{ // child
		//printf("child %d, parent is %d\n",getpid(), getppid());
	return(shell_launch(args));	
	}
}
	
char *shell_read(void){ // reads input from user ++
	int bufsize=shell_buffer; // sets buffer size to the defined size
	int count=0; // counts the size of the buffer
	char *buffer=malloc(sizeof(char)*bufsize); // allocates space for the string of arguments based on predifined buffer size
	int c; // for going through input characters
	if(!buffer){
		fprintf(stderr, " read error\n"); // if the buffer is NULL then the method exits
		exit(1);
	}
	while(1){ // loops until counter is larger than the buffer
		c=getchar();
		if(c==EOF||c=='\n'){ // if the reader hits an end of file(EOF) or an end of a line(\n), replace it with the terminating character of a string and return the buffer
			buffer[count]='\0';
			return buffer; // returns string of arguments
		}else{
			buffer[count]=c;
		}
		count++; // increments counter
		if(count>=bufsize){ // if the buffer is too small we make it larger
			bufsize+=shell_buffer; // adds the length of the buffer if there is not enough space
			buffer=realloc(buffer, bufsize); // reallocates more space for the now larger buffer
			if(!buffer){ // if the buffer is empty from the start
				fprintf(stderr, " read error\n");
				exit(1);
			}
		}
	}
}

char **shell_split(char *line){ // takes line and splits it into "tokens" which are the arguments ++								strtok()
	int bufsize=shell_buffer; // buffer is the size 
	int count=0; // counter
	char **tokens=malloc(sizeof(char*)*bufsize); // makes array of char pointers
	char *token; // char pointer for eack token
	if(!tokens){ // if token failes to initialize
		fprintf(stderr, " token error\n");
		exit(1);
	}
	token=strtok(line, shell_delim); // string parsing 			
	while(token!=NULL){
		tokens[count]=token;
		count++; // increments counter
		if(count>=bufsize){ // if the count passes the buff size
			bufsize+=shell_buffer; // increasing the size of the buffer size
			tokens=realloc(tokens, bufsize * sizeof(char*));
			if(!tokens){ // if tokens gets deleted by realloc somehow
				fprintf(stderr, " token error\n");
				exit(1);
			}
		}
		token=strtok(NULL, shell_delim); // token delimiters are made NULL
	}
	tokens[count]=NULL;
	return tokens; // returns the individual arguments
}

// main method												-----------------------------------------------------------------------------------------------
int main(int argc, char **argv){ // takes input and loops for the duration of the shell ++
	char *prompt=argc>1?argv[2]: "my257sh"; // assigns prompt's value
	char *line; // pointer to input strings
	char **args; // pointer to array of input string arguments
	int status; // initially 0, if 0 the loop terminates, every function sets it to 1
	struct sigaction new_action, old_action;
	new_action.sa_handler=sig_handler;
	new_action.sa_flags=SA_NODEFER | SA_ONSTACK;
	sigaction(SIGINT, &new_action, &old_action); // handles ^C
	signal(SIGHUP, sig_handler); // catches raised SIGHUP to end the program from exit function
	do{ // do-while loop for the shell that runs as long as the status isn't 0
		fprintf(stdout, "%s> ", prompt); // prints out the prompt for each line
		line=shell_read(); // reads the input arguments 	fgets()
		args=shell_split(line);	// splits the input arguments	strtok()
		status=shell_execute(args); // runs commands based off of the inputs and if 0 is returned then the loop exits
		free(line); // frees line before next input
		free(args); // frees args before next input
	}while(status); // continues looping until 0 is returned for status
	return 0; // returns 0 as program exits
} // end of the program