#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#define Buffer_size 512

typedef uint8_t BYTE;



int main(int argc, char *argv[])
{

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("error occured openiing the row file \n");
    }
    BYTE buffer[Buffer_size];
    size_t bytes_read;
    bool is_first_jpeg = false;
    FILE *current_file;
    char filename[100];
    int current_filenbr = 0;
    bool found_jpeg = false;
   
   
   
   
    if (argc  != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }


   
    /*
     // PseudoCode : //

    Repeat until end of card :
            
         
       
             ...
    Close any remaining file
    */

//    open memory card

    while (true)
    {
//        Read 512 Bytes into a buffer

        bytes_read = fread(buffer, sizeof(BYTE), Buffer_size, f);
        
        
        
        if (bytes_read == 0)
        {
            break; // ennd of file
        }
//        If start of new JPEG

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
           
            found_jpeg = true;
        
            if (!is_first_jpeg)
            {
                is_first_jpeg = true;
            }
            else 
            {
                // close the current file being written to, open new file 
                fclose(current_file); // previose file 000.jpg
            }
    
            sprintf(filename, "%03i.jpg", current_filenbr); // 000.jpg
            current_file =   fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), Buffer_size, current_file);
            current_filenbr ++; // filenbr = 1...
            
        }
        else
        {
            if (found_jpeg)
            {
                fwrite(buffer, sizeof(BYTE), Buffer_size, current_file);
            }
        }

    }
    fclose(f); // close my raw file 
    fclose(current_file);
    return 0 ;

}