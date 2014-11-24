/*
Derek Hua
CDA3101
Project2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int twosComp(std::string str);	//function returns 2's comp number in decimal form

int main()
{
	//input 
	std::string textfile;
	std::cout << "Enter input file name: ";
	getline(std::cin, textfile);
	std::ifstream input(textfile);

	std::string line;
	int address = 128;	//initial address

	std::vector<int> data;	//vector to hold data values
	int addressAfterBreak;

	if (input.is_open())
	{
		//disassembly output stream
		std::ofstream disassembly;
		disassembly.open("disassembly.txt");

		bool readNumbers = false;
		while (getline(input, line))
		{
			if (readNumbers == false)
			{
				//cat 1
				if (line[0] == '0' && line[1] == '0'){
					//J 0000
					if (line[2] == '0' && line[3] == '0' && line[4] == '0' && line[5] == '0'){
						std::string index;
						index = line.substr(6, 26);
						int num = twosComp(index);
						++num;
						int out = address - num;
						disassembly << line << '\t' << address << '\t' << "J #" << out << '\n';
						address += 4;
					}
					//BEQ 0010
					else if (line[2] == '0' && line[3] == '0' && line[4] == '1' && line[5] == '0'){
						std::string index;
						std::string s;
						std::string t;
						s = line.substr(6, 5);
						t = line.substr(11, 5);
						index = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(index);
						numi *= 4;
						disassembly << line << "\t" << address << "\t" << "BEQ  R" << nums << ", R" << numt << ", #" << numi << "\n";
						address += 4;
					}
					//BGTZ 0100
					else if (line[2] == '0' && line[3] == '1' && line[4] == '0' && line[5] == '0'){
						std::string index;
						std::string s;
						s = line.substr(6, 5);
						index = line.substr(16, 16);
						int nums = twosComp(s);
						int numi = twosComp(index);
						numi *= 4;
						disassembly << line << "\t" << address << "\t" << "BGTZ  R" << nums << ", #" << numi << "\n";
						address += 4;
					}
					//BREAK 0101
					else if (line[2] == '0' && line[3] == '1' && line[4] == '0' && line[5] == '1'){
						readNumbers = true;
						disassembly << line << "\t" << address << "\t" << "BREAK" << "\n";
						address += 4;
						addressAfterBreak = address;	//keep track of where address after the BREAK is
					}
					//SW 0110
					else if (line[2] == '0' && line[3] == '1' && line[4] == '1' && line[5] == '0'){
						std::string index;
						std::string s;
						std::string t;
						s = line.substr(6, 5);
						t = line.substr(11, 5);
						index = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(index);
						disassembly << line << "\t" << address << "\t" << "SW  R" << numt << ", " << numi << "(R" << nums << ")" << "\n";
						address += 4;
					}
					//LW 0111
					else if (line[2] == '0' && line[3] == '1' && line[4] == '1' && line[5] == '1'){
						std::string index;
						std::string s;
						std::string t;
						s = line.substr(6, 5);
						t = line.substr(11, 5);
						index = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(index);
						disassembly << line << "\t" << address << "\t" << "LW  R" << numt << ", " << numi << "(R" << nums << ")" << "\n";
						address += 4;
					}
				}
				//cat 2
				if (line[0] == '0' && line[1] == '1'){
					//ADD 0000
					if (line[12] == '0' && line[13] == '0' && line[14] == '0' && line[15] == '0'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "ADD  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//SUB 0001
					else if (line[12] == '0' && line[13] == '0' && line[14] == '0' && line[15] == '1'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "SUB  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//MUL 0010
					else if (line[12] == '0' && line[13] == '0' && line[14] == '1' && line[15] == '0'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "MUL  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//AND 0011
					else if (line[12] == '0' && line[13] == '0' && line[14] == '1' && line[15] == '1'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "AND  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//OR 0100
					else if (line[12] == '0' && line[13] == '1' && line[14] == '0' && line[15] == '0'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "OR  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//XOR 0101
					else if (line[12] == '0' && line[13] == '1' && line[14] == '0' && line[15] == '1'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "XOR  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
					//NOR 0110
					else if (line[12] == '0' && line[13] == '1' && line[14] == '1' && line[15] == '0'){
						std::string d;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						d = line.substr(16, 5);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numd = twosComp(d);
						disassembly << line << "\t" << address << "\t" << "NOR  R" << numd << ", R" << nums << ", R" << numt << "\n";
						address += 4;
					}
				}
				//cat 3
				if (line[0] == '1' && line[1] == '0'){
					//ADDI 0000
					if (line[12] == '0' && line[13] == '0' && line[14] == '0' && line[15] == '0'){
						std::string i;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						i = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(i);
						disassembly << line << "\t" << address << "\t" << "ADDI  R" << numt << ", R" << nums << ", #" << numi << "\n";
						address += 4;
					}
					//ANDI 0001
					else if (line[12] == '0' && line[13] == '0' && line[14] == '0' && line[15] == '1'){
						std::string i;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						i = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(i);
						disassembly << line << "\t" << address << "\t" << "ANDI  R" << numt << ", R" << nums << ", #" << numi << "\n";
						address += 4;
					}
					//ORI 0010
					else if (line[12] == '0' && line[13] == '0' && line[14] == '1' && line[15] == '0'){
						std::string i;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						i = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(i);
						disassembly << line << "\t" << address << "\t" << "ORI  R" << numt << ", R" << nums << ", #" << numi << "\n";
						address += 4;
					}
					//XORI 0011
					else if (line[12] == '0' && line[13] == '0' && line[14] == '1' && line[15] == '1'){
						std::string i;
						std::string s;
						std::string t;
						s = line.substr(2, 5);
						t = line.substr(7, 5);
						i = line.substr(16, 16);
						int nums = twosComp(s);
						int numt = twosComp(t);
						int numi = twosComp(i);
						disassembly << line << "\t" << address << "\t" << "XORI  R" << numt << ", R" << nums << ", #" << numi << "\n";
						address += 4;
					}
				}
			}
			else if (readNumbers == true)
			{
				disassembly << line << "\t" << address << "\t" << twosComp(line) << "\n";
				data.push_back(twosComp(line));	//vector that holds the data values
				address += 4;
			}

		}
		input.close();
		disassembly.close();
	}
	else std::cout << "Unable to open file";

	//-------------------------------------------------------------------------------------------------

	//address == last address
	int lastaddress = address -4;
	int lines = (address - 128) + 1; //amount of lines
	std::string *arr = new std::string[lines];

	std::ifstream dis("disassembly.txt"); //inputting disassembly file
	int i = 0;
	while (getline(dis, arr[i]) && i != lines)	//putting into an array
	{
		++i;
	}
	dis.close();

	//registers
	int R[32];
	for (int i = 0; i < 32; ++i)
	{
		R[i] = 0;
	}


	bool done = false;
	//simulation output stream
	std::ofstream simulation;
	simulation.open("simulation.txt");

	int cycle = 1;
	i = 0;
	while (!done)
	{
		// (address-128)/4 = index in array
		address = i * 4 + 128;
		// (address - addressAfterBreak) = index in vector

		//cat 1
		if (arr[i][0] == '0' && arr[i][1] == '0'){
			//J 0000
			if (arr[i][2] == '0' && arr[i][3] == '0' && arr[i][4] == '0' && arr[i][5] == '0'){
				std::string index;
				index = arr[i].substr(6, 26);
				int num = twosComp(index);
				int out = address - num + 1;

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				i = (out - 128) / 4; //new index
				++cycle;	//increment cycle
			}
			//BEQ 0010
			else if (arr[i][2] == '0' && arr[i][3] == '0' && arr[i][4] == '1' && arr[i][5] == '0'){
				std::string index;
				std::string s;
				std::string t;
				s = arr[i].substr(6, 5);
				t = arr[i].substr(11, 5);
				index = arr[i].substr(16, 16);

				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(index);

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				if (R[numt] == R[nums])
				{
					i = i + 1 + numi;
				}
				else ++i;
				++cycle;	//increment cycle
			}
			//BGTZ 0100
			else if (arr[i][2] == '0' && arr[i][3] == '1' && arr[i][4] == '0' && arr[i][5] == '0'){
				std::string index;
				std::string s;
				s = arr[i].substr(6, 5);
				index = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numi = twosComp(index);

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				if (R[nums] > 0)
				{
					i = i + 1 + numi;
				}
				else ++i;
				++cycle;	//increment cycle
			}
			//BREAK 0101
			else if (arr[i][2] == '0' && arr[i][3] == '1' && arr[i][4] == '0' && arr[i][5] == '1'){
				done = true;
				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";
			}
			//SW 0110
			else if (arr[i][2] == '0' && arr[i][3] == '1' && arr[i][4] == '1' && arr[i][5] == '0'){
				std::string index;
				std::string s;
				std::string t;
				s = arr[i].substr(6, 5);
				t = arr[i].substr(11, 5);
				index = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(index);

				int storeindex = numi + R[nums];
				storeindex = (storeindex - addressAfterBreak) / 4;
				data[storeindex] = R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;

			}
			//LW 0111
			else if (arr[i][2] == '0' && arr[i][3] == '1' && arr[i][4] == '1' && arr[i][5] == '1'){
				std::string index;
				std::string s;
				std::string t;
				s = arr[i].substr(6, 5);
				t = arr[i].substr(11, 5);
				index = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(index);
				int loadindex = numi + R[nums];
				loadindex = (loadindex - addressAfterBreak) / 4;
				R[numt] = data[loadindex];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
		}
		//cat 2
		if (arr[i][0] == '0' && arr[i][1] == '1'){
			//ADD 0000
			if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '0' && arr[i][15] == '0'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] + R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;

			}
			//SUB 0001
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '0' && arr[i][15] == '1'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] - R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//MUL 0010
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '1' && arr[i][15] == '0'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] * R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//AND 0011
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '1' && arr[i][15] == '1'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] & R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//OR 0100
			else if (arr[i][12] == '0' && arr[i][13] == '1' && arr[i][14] == '0' && arr[i][15] == '0'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] | R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//XOR 0101
			else if (arr[i][12] == '0' && arr[i][13] == '1' && arr[i][14] == '0' && arr[i][15] == '1'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = R[nums] ^ R[numt];

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//NOR 0110
			else if (arr[i][12] == '0' && arr[i][13] == '1' && arr[i][14] == '1' && arr[i][15] == '0'){
				std::string d;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				d = arr[i].substr(16, 5);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numd = twosComp(d);

				R[numd] = ~(R[nums] | R[numt]);

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
		}
		//cat 3
		if (arr[i][0] == '1' && arr[i][1] == '0'){
			//ADDI 0000
			if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '0' && arr[i][15] == '0'){
				std::string i2;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				i2 = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(i2);

				R[numt] = R[nums] + numi;

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				++i;
				++cycle;
			}
			//ANDI 0001
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '0' && arr[i][15] == '1'){
				std::string i2;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				i2 = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(i2);

				R[numt] = R[nums] & numi;

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				i++;
				++cycle;
			}
			//ORI 0010
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '1' && arr[i][15] == '0'){
				std::string i2;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				i2 = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(i2);

				R[numt] = R[nums] | numi;

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				i++;

			}
			//XORI 0011
			else if (arr[i][12] == '0' && arr[i][13] == '0' && arr[i][14] == '1' && arr[i][15] == '1'){
				std::string i2;
				std::string s;
				std::string t;
				s = arr[i].substr(2, 5);
				t = arr[i].substr(7, 5);
				i2 = arr[i].substr(16, 16);
				int nums = twosComp(s);
				int numt = twosComp(t);
				int numi = twosComp(i2);

				R[numt] = R[nums] ^ numi;

				simulation << "--------------------\nCycle:" << cycle << arr[i].substr(32) << "\n\n";
				//registers print
				simulation << "Registers\n";
				simulation << "R00:\t";
				for (int x = 0; x < 8; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR08:\t";
				for (int x = 8; x < 16; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR16:\t";
				for (int x = 16; x < 24; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\nR24:\t";
				for (int x = 24; x < 32; ++x)
				{
					simulation << R[x] << "\t";
				}
				simulation << "\n\n";

				//data print
				simulation << "Data\n";
				int datasize = (lastaddress - addressAfterBreak) / 4 + 1;
				for (int x = 0; x < datasize; ++x)
				{
					if (x % 8 == 0) simulation << "\n" << (x * 4) + addressAfterBreak << ":\t";
					simulation << data[x] << "\t";
				}
				simulation << "\n\n";

				i++;
				++cycle;
			}
		}
	}
	simulation.close();

	std::cout << "disassembly.txt and simulation.txt created." << std::endl;
	return 0;
}



int twosComp(std::string str)
{
	double sum = 0;
	double exponent = 0;
	for (int i = str.length() - 1; i >= 0; --i) 
	{
		if (i == 0 && str[i] == '1'){	//MSB
			sum += -1 * (pow(2.0, exponent));
		}
		else if (str[i] == '1'){
			sum += pow(2.0, exponent);
		}
		++exponent;
	}
	return (int)sum;
}
