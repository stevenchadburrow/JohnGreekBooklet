#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	system("ls TEX-Edit > Temp.txt");
	
	FILE *contents = NULL;

	contents = fopen("Temp.txt", "rt");
	if (!contents) return 1;

	int bytes = 1;
	char filename[256];

	char command[512];

	while (bytes > 0)
	{
		bytes = fscanf(contents, "%s", filename);

		if (bytes > 0)
		{
			sprintf(command, "pdflatex -output-directory PDF-Edit TEX-Edit/%s", filename);

			system(command);
		}
	}

	fclose(contents);

	system("rm Temp.txt");

	system("ls PDF-Edit > Temp.txt");

	contents = NULL;

	contents = fopen("Temp.txt", "rt");
	if (!contents) return 1;

	bytes = 1;

	while (bytes > 0)
	{
		bytes = fscanf(contents, "%s", filename);

		if (bytes > 0)
		{
			if (filename[0] == 'P') // all of the PrintedLatexVersion stuff
			{
				sprintf(command, "pdftk PDF-Edit/%s cat 2-end output PDF-Edit/Another.pdf", filename);
	
				system(command);
	
				sprintf(command, "rm PDF-Edit/%s ; mv PDF-Edit/Another.pdf PDF-Edit/%s", filename, filename);
	
				system(command);
			}
		}
	}

	system("rm Temp.txt");

	system("pdftk PDF-Edit/*.pdf cat output JohnBook.pdf");

	return 0;
}
