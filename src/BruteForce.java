import java.util.Arrays;
import java.util.Scanner;

public class BruteForce {

	private int stringLength;
	private final char[] alphabetMinuscule = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	private final char[] alphabetMajuscule = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	private final char [] chiffres = {'0','1','2','3','4','5','6','7','8','9'};
	private double nbCombi = 1;
	private String alphabet;
	private char[] chars;
	private char[] characters; // possibles characters 
	private int number;
	private char[] password;
	private long start;
	
	public BruteForce(int number,String alphabet2, int stringLength) {

		this.number = number;
		this.alphabet = alphabet2;
		initializeAlphabet();
		this.stringLength = stringLength;
		chars = new char[stringLength];
		Arrays.fill(chars, 0, chars.length, characters[0]); // initialize array	
		run();
	}

	private void initializeAlphabet() {
		if(alphabet.equals("min"))
			characters = alphabetMinuscule;
		else if(alphabet.equals("maj"))
			characters = alphabetMajuscule;
		else if(alphabet.equals("min-maj")) { 
			characters = new char[alphabetMajuscule.length+alphabetMinuscule.length]; // concatenate min and max alphabets
			System.arraycopy(alphabetMinuscule, 0,characters, 0, alphabetMinuscule.length); // add min 
			System.arraycopy(alphabetMajuscule, 0,characters, alphabetMinuscule.length, alphabetMajuscule.length); // add max
		}
		else if(alphabet.equals("min-maj-chiffre")) { // concatenate min, max and  digit alphabets
			characters = new char[alphabetMajuscule.length+alphabetMinuscule.length+10];
			System.arraycopy(alphabetMinuscule, 0,characters, 0, alphabetMinuscule.length); // add min 
			System.arraycopy(alphabetMajuscule, 0,characters, alphabetMinuscule.length, alphabetMajuscule.length);  // add max
			System.arraycopy(chiffres, 0,characters, chiffres.length-chiffres.length, chiffres.length); // add digit
		}
		
	}

	private void  run() {
		try {
			System.out.println("Case number "+number +" : "+ stringLength+ " lettres, alphabet : " +alphabet);
			System.out.println("Number of availables characters " +characters.length);
			System.out.println("Number of possible combinations:  " +Math.pow(characters.length,chars.length));
			System.out.println();
			System.out.println("Enter a String with " +stringLength +" caracters with " +alphabet +" alphabet");
			Scanner sc = new Scanner(System.in);
			password = sc.nextLine().toCharArray();
			start = System.nanoTime();
			runAux(new StringBuilder().append(chars),chars.length-1,0);
			//runAux2(chars,chars.length-1,0);	
			sc.close();
			end();
		} catch (InterruptedException e) {e.printStackTrace();}
	}


	private void runAux(StringBuilder s,int i,int lettre) throws InterruptedException {	
		StringBuilder s2;
		if(i==0){ // right of string : print all possibles last characters of the string
			s2 = new StringBuilder().append(s.toString()); // faster than new StringBuilder(s.toString());
			for (int j = 0; j < characters.length; j++) {
				s2.setCharAt(s.length()-1,  characters[j]);	
				//System.out.println(s2);
				char [] pass = s2.toString().toCharArray();
				if(Arrays.equals(pass, password)) {
					System.out.println();
					System.out.println("Combinaison trouvée " +s2 +" combinaison n° " +nbCombi);	
					end();
				}
				nbCombi++;
			}
		}
		else { // begin or middle of the string 
			runAux(s,i-1,0);	// just go to the right of the string

			if(lettre != characters.length-1) {  // if non on end of possible characters 
				s2 = new StringBuilder().append(s.toString());
				s2.setCharAt(s.length()-i-1,  characters[lettre+1]);
				runAux(s2,i,lettre+1); 
			}	
		}				
	}

	@SuppressWarnings("unused")
	private void runAux2(char [] s,int i,int lettre) throws InterruptedException {	
		char [] s2 = new char[s.length];
		if(i==0){ // right of string : print all possibles last characters of the string
			System.arraycopy(s, 0, s2, 0, s.length);
			for (int j = 0; j < characters.length; j++) {
				s2[s.length-1] = characters[j];
				System.out.println(new String(s2));
				if(Arrays.equals(s2,password)) {
					System.out.println();
					System.out.println("Combinaison trouvée " +new String(s2) +" combinaison n° " +nbCombi);	
					end();
				}
				nbCombi++;
			}
		}
		else if(i>0){ // begin or middle of the string 
			runAux2(s,i-1,0);	// just go to the right of the string
			if(lettre != characters.length-1) {  // if non on end of possible characters 
				System.arraycopy(s, 0, s2, 0, s.length);
				s[s.length-i-1] = characters[lettre+1];
				runAux2(s2,i,lettre+1); 
			}	
		}				
	}
	
	private void end() {
		long duree = (long) ((System.nanoTime() - start) / 1e3);	
		System.out.println("Duration  : ");
		System.out.println("-> : " + duree +" µs" +" | "+ duree/ 1e3 +" ms" +" | "+ duree/ 1e6 +" s");
		System.out.println("Number of combinations :  " +nbCombi);
		System.out.println(); System.out.println();	
		System.exit(0);
	}

	@SuppressWarnings("unused")
	public static void main(String[] args) throws InterruptedException {
		BruteForce cas1 = new BruteForce(1,"min", 6);

		BruteForce cas2 = new BruteForce(2,"min-maj", 6);

		//BruteForce cas3 = new BruteForce(3,"min-maj-chiffre", 6);

		//BruteForce cas4 = new BruteForce(4,"min", 7);
		//               
		///BruteForce cas5 = new BruteForce(5,"min-maj", 7);
		//               
		// BruteForce cas6 = new BruteForce(6,"min-maj-chiffre", 7);
		//               
		// BruteForce cas7 = new BruteForce(7,"min", 8);
		//               
		// BruteForce cas8 = new BruteForce(8,"min-maj-chiffre", 8);


	}

}