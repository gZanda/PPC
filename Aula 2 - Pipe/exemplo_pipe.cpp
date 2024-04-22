#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(){
int fd[2],n; 
pid_t pid; 
if( pipe(fd)<0 ) {
	cout << "Pipe nao criado" << endl;
	_exit(0);
}
if( (pid=fork())<0 ) {
	cout <<"Processo nao criado"<< endl;
	_exit(0);
}
if ( pid>0 ) {  
	cout << "Processo pai" << endl;
	char line[128];
	close(fd[1]);
	n = read(fd[0],line,128);
	write(1, &line[0], n);/* escreve no stdout*/
	close(fd[0]);
	kill(pid,SIGKILL); /* elimina processo descendente */
	_exit(0); 
}	
if ( pid==0 ) {
	char msg[8]={'B','o','m',' ','d','i','a','\n'};
	close( fd[0] );
	write( fd[1], &msg[0], 8);
	close( fd[1] );
	pause(); 
}
return 0;
}



