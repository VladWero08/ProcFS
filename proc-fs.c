#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>


typedef struct proc {
    int PID, numberOfChildren;
    struct proc *children[201];
    char *status;
} process;

process *rootOfFS;


int constructTreeOfProcesses(process *root, int PID) {
////    MOCK-UP IMPLEMENTATION
////    when any syscall fails -> return PID
//    root = malloc(sizeof(process));
//    root->PID = PID;
//
//    int fd = open("/proc/PID/task/PID/children", O_RDONLY);
//    char childrenList[12031];
//    read(fd, childrenList, 12031);
//    root->numberOfChildren = 0;
//
//    fd = open("/proc/PID/status", O_RDONLY);
//    root->status = malloc(sizeof(char) * 82738);
//    read(fd, root->status, 82738);
//
//    int returnStatus;
//    for(int i=0; i<strlen(childrenList); i++) {
//        returnStatus = constructTreeOfProcesses(root->children[i], childrenList[i]);
//        root->numberOfChildren++;
//
//        if (!returnStatus)
//            return returnStatus;
//    }
//
//    return 0;
}


process* getProcess(char *path);


static int _getattr(const char *path, struct stat *status);


static int _readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo){
    
    process* target = getProcess(path);

    if(target != NULL){
        char buf[200];
        int index = 0;

        while (buffer && *(char *) buffer != '\0')  // buf = buffer content
        {				
            buf[index++] = *(char *) buffer;
            (buffer)++;
        }


        for (int i = 0; i < node->numberOfChildren; i++) 
        {
            int pid = node->children[i]->PID;
            char pidChar[100];
            int lenPid = 0;

            while (pid)
            {
                pidChar[lenPid++] = (pid % 10) + '0';
                pid /= 10;
            }

            while (lenPid)  // buf concatenare cu pid
            {			
                buf[index++] = pidChar[lenPid - 1];
                lenPid--;
            }

            buf[index++] = '/';
        }

        buf[index++] = '\0'; 

        buffer = buf; // buffer points to the new location
    }
    else{
        perror("operation failed: ");
        return errno;
    }

    return 0;
}



static int _read(const char *path, char *buffer, size_t, off_t, struct  fuse_file_info *fileInfo);


static struct fuse_operations implementedOperations = {
    .getattr = &_getattr,
    .readdir = &_readdir,
    .read = &_read
};


int main(int argc, char **argv) {
    int operationStatus;
    if ((operationStatus = constructTreeOfProcesses(rootOfFS, 1)) != 0) {
        fprintf(stdout, "Tree construction failed at process #%d", operationStatus);
        fprintf(stderr, "Tree construction failed at process #%d", operationStatus);
        return 1;
    }

    return fuse_main(argc, argv, &implementedOperations, NULL);
}