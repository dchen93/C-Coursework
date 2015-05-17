// Commandline Usage (assuming compiled output file is named mostRecent): mostRecent fileName[ fileName]
//
// Differences from python version:
// I decided on a more direct approach to checking mount options for atime by iterating though the mtab
// 		This is triggered by prompting the user after facing the first error, to display atime mount options
// I decided to not include duplicate filename checking for this one, just because if there are no duplicates, it's an unnecessary overhead


#include <stdio.h>
#include <mntent.h> // to check mount options
#include <sys/stat.h> // for file attributes
#include <time.h> // for time_t struct


void checkFS();
void compare(int count, char *fileNames[]);


int main(int argc, char *argv[]){
	//check 
	if(argc == 1){
		//assume compiled output file is named: mostRecent
		printf("Error: missing arguments\nUsage: mostRecent fileName[ fileName]\n");
		return 0;
	}

	//compare access times, no need to keep program name
	compare(argc - 1, argv + 1);

	return 0;
}


//Issue warnings for any attached file system options
void checkFS(){
	FILE *fp = setmntent("/etc/mtab", "r");
	struct mntent *entry;

	while((entry = getmntent(fp))){
		if(hasmntopt(entry, "noatime") != NULL){
			printf("Warning: %s has noatime mount option\n", entry->mnt_fsname);
		}else if(hasmntopt(entry, "nodiratime") != NULL){
			printf("Warning: %s has nodiratime mount option\n", entry->mnt_fsname);
		}else if(hasmntopt(entry, "relatime") != NULL){
			printf("Warning: %s has relatime mount option\n", entry->mnt_fsname);
		}
	}
	endmntent(fp);
	printf("\n");
}


void compare(int count, char *fileNames[]){
	int i, check = 0; //check is a flag to check if the user wishes to see mount options
	struct stat attrib;
	time_t newestAtime = 0;
	char *newestPath, userChoice;

	for(i = 0; i < count; i++){
		if(stat(fileNames[i], &attrib) != -1){ //verify file exists
			if(attrib.st_atime > newestAtime){ //compare atimes
				newestAtime = attrib.st_atime;
				newestPath = fileNames[i];
			}
		}else{
			//ask if user wishes to view file system option warnings
			if(check == 0){
				printf("Error locating access time for file: %s\nWould you like to view File System mount option warnings? (y/n): ", fileNames[i]);
				userChoice = getchar(); //use getchar rather than scanf to avoid buffer overflow

				//verify correct input
				while(userChoice != 'Y' && userChoice != 'y' && userChoice != 'N' && userChoice != 'n'){
					printf("Enter 'y' or 'n': ");
					while((userChoice = getchar()) != '\n' && userChoice != EOF); //flush buffer
					userChoice = getchar();
				}

				if(userChoice == 'Y' || userChoice == 'y' ){
					checkFS();
				}

				check = 1; //only ask once
				continue;
			}

			printf("Error locating access time for file: %s\n", fileNames[i]);
		}
	}

	//verify at least one file was found
	if(newestAtime == 0){
		printf("Unable to locate access times for listed files\n");
	}else{
		printf("%s\n", newestPath);
	}
}