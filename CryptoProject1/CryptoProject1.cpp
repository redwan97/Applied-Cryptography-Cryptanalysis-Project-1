// CryptoProject1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictionary.h"
#include "LetterDistribution.h"
#include "MultiShiftDecryptor.h"
#include "Text.h"
#include "Encrypt.h"
#include "SymbolDecryptor.h"


#include <vector>
#include <string>
#include <iostream>


int main()
{	
	/*Testing using encryption function*/
	//std::string p = loadDefaultDictionary()[3];
	//p = encrypt(p);
	//p = encrypt2(p);

	vector<string> ciphers;
	std::string option;
	std::string ynOption;
	std::string ctext0,ctext1, ctext2, ctext3, ctext4, ctext5, ctext6, ctext7, ctext8, ctext9;
	std::vector<std::string> dict = loadDefaultDictionary();
	std::cout << "\t\t\t**** Applied Cryptography Project 1 ****\n" << std::endl;
	std::cout << "Authors: Redwanul (rm4243) and William (wcu201)" << std::endl;
	std::cout << "Please specify if you are checking Test 1 or Test 2, (Indicate 1 or 2): ";
	std::cin >> option;
	std::cout << endl;

	if (option == "Test 1" || option == "1" || option == "test 1" || option == "test1" || option == "Test1" || option == "one" || option == "t1") {
		std::cout << "For the purpose of the project, program assumes ciphertext originates from some plaintext in provided dictionary." << std::endl;
		std::cout << "Note this program can find plaintext-ciphertext pairs and only dictionary 1 has been provided to this program.\n" << std::endl;
		std::cout << "Are you typing in ciphertexts? Indicate yes or no. If no, preset ciphertexts will be used: ";
		std::cin >> ynOption;
		if (ynOption == "Y" || ynOption == "Yes" || ynOption == "y" || ynOption == "yes") {
			std::cout << "Please enter the ciphertext to be decrypted : " << std::endl;
			std::cin >> ctext0;
			ciphers.push_back(ctext0);
		}
		else if (ynOption == "N" || ynOption == "No" || ynOption == "n" || ynOption == "no") {
			ctext0 = "fzpkmlgxzrgmlqynpzrgoscybcdmjgzrcby pzqfjwycjcezlawyfclncaiycaskclgagqkytzjsrzyjglecpqyzapm zrgaykgqkzppgzecydpsgrjcqqlcqqynzrrcpgleyclz jcqyrpztmgqylwknfqydpzrpgagbcqyzuziclcpympbspcyrpg sjzrgmlycjgagrylmltgz jcyesgjcqypzsamsqjwycsajgbczlyctzlecjgqrynpcmncpzrgtcynzrfmeclwydpzkcqykcbgskygltgz gjgrgcqypcrpzglqyapzliazqcyzuiuzpbcpyqrmnuzrafyqs ajglgazjygppgezrmpqyjcrrsacyqigbmmcbydmlbcpyrcckydslesqcqynsptgcuqyjmleqfmryzddzgpcqyuczpgleyhsbmypcqcrrjcyzlrcbzrcyglmncpz jcynglumpkynskncpyzllsjyzlrcnmqg";
			ctext1 = "qsppclbcpccybmaskclryqnsligcqryamoscrrcbyz zrgqyjczqcfmjbylsajcgydmeeglcqqyeclmzyrpzgrmpqy jmai sqrcpyqsncpnmqgrgmlqydjzkqyqspnpgxcbyfmlafmyacrcpzyrmyrpzlqkgrynqwafmjyuglrcpcbyepslrglejwyafcznlcqqyrpzlqjzrgmlyjz mpcpyjgqqmkclcqqyazpztzlqzpgcqypcdjcvcqymtcpcvrclbqy grrcpysnjgdryqrpzrcydgjjcpyasnmjzcbyzsrmkzrgaykzafpccylmlnzpzqgrgayslzqfzkcby pzeewyrwngcpynmrclagcqyepcwlcqqyesjncbykzqmlumpiy jzlbgqfcpybgqiqydzbczuzwympgezkgqykzlspcpymjgtcqycleglcyjmmrcbyufgrcfzjjygkncpgjqyqfzbmu mvyhz  gleycvnmprq";
			ctext2 = "pizshzmi kmvlmlhzmkmlm hqvmjzqiamhntwdmzfhidsdizlmzhdiamzjmlhkwuxtikmvkfh qsphkwuxizaumvamlhlmxmvlijtfhittqamziaqwv hpmilikpmhji smanbt huitwkktb qwv hkbjq aqkhpqvahpmillzm  m hbvnzwks hsmtwqlithaziv tbkmvahnqlmtqaqm hqv azbkaqwvithozixpmlhjismzh bxmzjh xmkazw kwxqm hjq uizshbvkivvqm ahlmaikpijqtqafhtmalwdvhybmzbtwb tfhbv aikshkbzltqvohkpiqvmlhxwqvafhlzqxxmz htizkph xmzuqkqlmhqvmeazqkijqtqafhivammlhquxzwcq qvohrixmhquxwvlmzijtfhtqapwozixpqkhdqvotma hilcmva hazqxtqkiaqvohozwdtqvohnm kbmh itijqtqa";
			ctext3 = "mnfveytwhhdyxtmpbkeyxtuvlbgmaltwywutwayumykrtkumykltkyxyiehrtgbuwbgufbxythzzykyytikyoygmboyertmug bveygylltvyufrtheb ukwabwuetfbwkhvnltbgmygxlt ueougbsytbgxyebveytmnvbg lthoykwhheltkheehoyktfueuxkhbmteh purltzkbeebg tldbgdltuzzbkfumboyertzeumzhhmlthoykleyyiltwhglb ghkltwhfieymyltyliuxkbeeytvhhfltkyiuoyxthzurltdyygltxbghlunkltkykhnmyxtwhglb gfygmltobwmbfeylltilrwahiarlbwuetwanwdeytuxfbllbvbebmrtfneymyyktxyylwueumbg thoukrtvhpphptullblbtzhkytmnvvbylmtohwumboyertzbebueertikyylmuveblateuwjnykykltlik";
			ctext4 = "yrhaqhvritvduvuqhvtvuviqzdvshzrjvqwbemvhoqrmamrhuvhqmrjvhsvuqtecfbrtvdtoqizayqtecfrhjcvdjvuquvfvdursboqrbbzjvhrjzediqyvrurtyvqsriavjwkbiqcrbettbkizediqtkszijztqyzdjqyvruuhviiviqkdwhetaiqavbezurbqjhrdibktvdjqwzuvbzjzviqzdijhktjzedrbqxhrfyvuqsravhqikfvhsqifvtjheitefzviqszicrhaqkdtrddzvijquvjrtyrszbzjoqbvjuemdqgkvhkbekiboqkdijrtaqtkhubzdxqtyrzdvuqfezdjoquhzffvhiqbrhtyqifvhcztzuvqzdvnjhztrszbzjoqrdjvvuqzcfhelzizdxq rfvqzcfeduvhrsboqbzjyexhrfyztqmzdxbvjiqrulvdjiqjhzfbztrjzdxqxhembzdxqwvitkvqirbrszbzj";
			ctext5 = "vwodngbeqqmgfbvyktngfbcdukpvjubegecbejgcvgt btcvgtubtgfgrnq bpkcekpcokfgbqhhgtggbrtgxgpvkxgn bvcpikdngpguubdgco bqnkictejkecnboketqdwubkpvgpfubicnxcpkagbkpfgnkdngbvwdkpiubqxgteqqnubtqnnqxgtbocncftqkvbnqiyc ubhtknnkpibumkpmubchhktocvkxgn bhncvhqqvubqxgtunggrubeqpukipqtubeqorngvgubgurcftknngbdqqoubtgrcxgfbqhc ubmggpubfkpqucwtubtgtqwvgfbeqpukipogpvubxkevkonguubru ejqrj ukecnbejwemngbcfokuukdknkv bowngvggtbfgguecncvkpibqxct bdqyyqybcuukukbhqtgbvwddkguvbxqecvkxgn bhknkcnn brtgguvcdnkujbnceswgtgtuburt";
			ctext6 = "pizshzmi kmvlmlhzmkmlm hqvmjzqiamhntwdmzfhidsdizlmzhdiamzjmlhkwuxtikmvkfh qsphkwuxizaumvamlhlmxmvlijtfhittqamziaqwv hpmilikpmhji smanbt huitwkktb qwv hkbjq aqkhpqvahpmillzm  m hbvnzwks hsmtwqlithaziv tbkmvahnqlmtqaqm hqv azbkaqwvithozixpmlhjismzh bxmzjh xmkazw kwxqm hjq uizshbvkivvqm ahlmaikpijqtqafhtmalwdvhybmzbtwb tfhbv aikshkbzltqvohkpiqvmlhxwqvafhlzqxxmz htizkph xmzuqkqlmhqvmeazqkijqtqafhivammlhquxzwcq qvohrixmhquxwvlmzijtfhtqapwozixpqkhdqvotma hilcmva hazqxtqkiaqvohozwdtqvohnm kbmh itijqtqa";
			ctext7 = "ngxqfxkgyiktjkjfxkikjkyfotkhxogzkflrubkxdfgbqbgxjkxfbgzkxhkjfiusvrgiktidfyoqnfiusvgxzsktzkjfjkvktjghrdfgrrozkxgzoutyfnkgjginkfhgyqkzl ryfsgruiir youtyfi hoyzoifnotzfnkgjjxkyykyf tlxuiqyfqkruojgrfzxgtyr iktzflojkrozokyfotyzx izoutgrfmxgvnkjfhgqkxfy vkxhfyvkizxuyiuvokyfhoysgxqf tigttokyzfjkzginghorozdfrkzjubtfw kx ru yrdf tyzgiqfi xjrotmfingotkjfvuotzdfjxovvkxyfrgxinfyvkxsoiojkfotkczxoighorozdfgtzkkjfosvxuaoyotmfpgvkfosvutjkxghrdfroznumxgvnoifbotmrkzyfgjaktzyfzxovroigzotmfmxubrotmflkyi kfygrghoroz";
			ctext8 = " atislgjvvrlkg cpyslkghizpu ozgjljhgjolh lyegyh lyzgylklwsveguphjpuhtpklgvmmlyllgwylblu pblseg hunpislulzzgilhtegvspnhyjopjhsgtpjyviazgpu lukzgnhsbhupflgpuklspislg aipunzgvblyjvvszgyvssvblygthshkyvp gsvnchezgmypsspungzrpurzghmmpyth pblsegmsh mvv zgvblyzsllwzgjvuzpnuvyzgjvtwsl lzglzwhkypsslgivvtzgylwhblkgvmhezgrlluzgkpuvzhayzgylyva lkgjvuzpnutlu zgbpj ptslzzgwzejovwoezpjhsgjoajrslghktpzzpipsp egtasl llygkllzjhsh pungvbhyegivccvcghzzpzpgmvylg aiiplz gbvjh pblsegmpsphssegwyllz hispzogshjxalylyzgzwy";
			ctext9 = "tbfc  ttodxbgosphxjt mopfaxvtfoqxgtrhoxbghp  gohpuuthporcad xpbrtgovcjtfbcfgwxdo prtkcfzgodftrxcigbtggoqtsxntbgoxaapri pht mosxgxbutrhobir tcbxrgoqxftatgoapx qpvgoqtwpjtgotbwpbrtou cddxtghoqfihxgagoftvxghtftsogx tbrtsohieitgocfmltgorcss tfoibstfgxvbtsoaprzxbhcgwoaxgtad cmatbhodtprtapztfgod tpsxbvgospbsxuxrphxcbod phmdigtgogkxvosctfoftgwcktsoeipsfpbv tgo crihcfmotbrpdgi tgoqpksxtgokcc dprzojp iphtsoap cscfcig mogwx  orfmcvtbxtgozbckbosxghfoqcbgpxoacfp toaxfpvtogzxhopeiprpstgodxocjtfrcaacbou xddpb";
			
			ciphers.push_back(ctext0);
			ciphers.push_back(ctext1);
			ciphers.push_back(ctext2);
			ciphers.push_back(ctext3);
			ciphers.push_back(ctext4);
			ciphers.push_back(ctext5);
			ciphers.push_back(ctext6);
			ciphers.push_back(ctext7);
			ciphers.push_back(ctext8);
			ciphers.push_back(ctext9);
		}
		else {
			std::cout << "Invalid Input. Exiting !!" << std::endl;
			return 0;
		}
		std::cout << std::endl;
		
		for (int x = 0; x < ciphers.size(); x++) {
			bool cracked = false;
			for (int i = 0; i < dict.size(); i++) {
				for (int j = 0; j < 28; j++) {
					Decryptor* dec = new MultiShiftDecryptor(i, dict[i], ciphers[x], j + 1);
					if (dec->decrypt()) {
						dec->getExplanation();
						std::cout << "Program's guess of plaintext is: " << dict[i] << std::endl;
						cracked = true;
						delete dec;
						std::cout << std::endl << std::endl;
						break;
					}
					delete dec;
				}
			}
			if (!cracked) { std::cout << "Could not decode ciphertext. Please have mercy :( " << std::endl; }
		}
		/*Testing on simple plaintexts*/
		/*
		std::string s, c;
		s = "hi how are you dude";
		c = encrypt(s);
		bool cracked = false;
		for (int i = 0; i < 40; i++) {
			Decryptor* d =  new MultiShiftDecryptor(0, s, c, i+1);
			if (d->decrypt()) {
				d->getExplanation();
				cracked = true;
				delete d;
				break;
			}
			delete d;
		}
		if (!cracked) { std::cout << "Could not decode ciphertext. Please have mercy :( " << std::endl; }
		*/

		/*Testing header file correctness*/
		/*
		for (auto x : loadDefaultDictionary()) {					// for each element in dictionary that is returned by loadDefaultDict,
			Text aText(x);											//	create a Text for it
			aText.getDistribution().printFreqTable();				//	print the distribution form the text
			std::cout << std::endl;
		}
		*/
	}
	else if (option == "Test 2" || option == "2" || option == "test 2" || option == "test2" || option == "Test2" || option == "two" || option == "t2") {
		//int keySize;

		std::cout << "Conducting Test 2..." << std::endl;
		std::cout << "Please enter the txt file containing the ciphertext to be decrypted : ";
		std::cin >> ctext1;

		//std::cout << "Please enter key length : ";
		//std::cin >> keySize;
		//std::getline(std::cin, ctext);
		SymbolDecryptor* symbolDec = new SymbolDecryptor();
		symbolDec->decryptFile(ctext1, "plaintext_dictionary_2.txt");
	}
	else {
		std::cout << "Invalid Input. Exiting !!" << std::endl;
	}


    return 0;
}

