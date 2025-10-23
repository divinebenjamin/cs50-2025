#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;
 
int main(int argc, char *argv[])
{
  // Verify command-line    
  if(argc != 2)
  {
    printf("Usage: ./recover cardfile\n");
    return 1;
  }
 
  // 
  BYTE buffer[BLOCK_SIZE];

  // open card file
  FILE *card = fopen(argv[1], "r");
  if(card == NULL)
  {
    printf("Could not open file\n");
    return 1;
  }

  // image file tracking
  int count = 0;
  char filename[8];
  FILE *img = NULL;


  // read 512bytes of memory from card
  while(fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
  {
    // check if it's a jpeg
    if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
      // close previous jpg file
      if(img != NULL)
      {
        fclose(img);
      }

      // open and write new jpeg file
      count++;
      sprintf(filename, "%03i.jpg", count);
      img = fopen(filename, "w");
    }
    
    // keep writing to opened file
    if(img != NULL)
    {
      fwrite(buffer, 1, BLOCK_SIZE, img);
    }

  }

  // close files
  fclose(card);
  if (img != NULL)
  {
    fclose(img);
  }
  
  return 0;
}