import java.util.Arrays;

public class BruteForce {

	private int stringLength;
	private final char[] alphabetMinuscule = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	private final char[] alphabetMajuscule = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	private final char [] chiffres = {'0','1','2','3','4','5','6','7','8','9'};
	private double nbCombi = 0;
	
	//private final char[] lettres = { 'a', 'b', 'c'};

	private char[] chars;
	private char[] lettres;
	public BruteForce(String alphabet, int len) {
		if(alphabet.equals("min"))
			lettres = alphabetMinuscule;
		else if(alphabet.equals("maj"))
			lettres = alphabetMajuscule;
		else if(alphabet.equals("min-maj")) {
			lettres = new char[alphabetMajuscule.length+alphabetMinuscule.length];
			System.arraycopy(alphabetMinuscule, 0,lettres, 0, alphabetMinuscule.length);
			System.arraycopy(alphabetMajuscule, 0,lettres, alphabetMinuscule.length, alphabetMajuscule.length);
		}
		else if(alphabet.equals("min-maj-chiffre")) {
			lettres = new char[alphabetMajuscule.length+alphabetMinuscule.length+10];
			System.arraycopy(alphabetMinuscule, 0,lettres, 0, alphabetMinuscule.length);
			System.arraycopy(alphabetMajuscule, 0,lettres, alphabetMinuscule.length, alphabetMajuscule.length);
			System.arraycopy(chiffres, 0,lettres, chiffres.length-chiffres.length, chiffres.length);
		}
			
		this.stringLength = len;
		chars = new char[stringLength];
	    Arrays.fill(chars, 0, chars.length, lettres[0]);
		//run2(chars);
	    run();
	}

	private void  run() {
		try {
			long start = System.nanoTime();
			RunAux(chars, chars.length-1,0);
			long duree = (long) ((System.nanoTime() - start) / 1e3);
			long duree2 = (long) (duree / 1e3);
			System.out.println("Durée  : " + duree +" µs");
			System.out.println("Durée  : " + duree2 +" ms");
			System.out.println("NbCombinaisons:  " +nbCombi);
			System.out.println();			
		} catch (InterruptedException e) {e.printStackTrace();}
	}
	
	@SuppressWarnings("unused")
	private void run2(char [] s) {
		int i= s.length-1, lettre = 1;
		
		while(! end(s)) {
			if(i == s.length) {
				for (int j = 0; j < lettres.length; j++) {
					s[s.length-1] = lettres[j];
					print(s);				
				}
				i--;
			}
			if(lettre == lettres.length) {
				i--;
				lettre = 0;
			}
			else{
				if(i != s.length-1) {
					
					s[s.length-1] = lettres[0];
					s[i] = lettres[lettre];
					lettre ++;
					i++;
					if(lettre == lettres.length && i != 0)
						lettre--;		
				}
			}		
		}
	}
	
	private boolean end(char [] tab) {
		String s = new String(tab);
		char [] tab2 = new char[tab.length];
		Arrays.fill(tab2,0,s.length(),lettres[lettres.length-1]);
		String s2 = new String(tab2);
		boolean b = s.equals(s2);
		return b;
		
	}
	private void RunAux(char[] s,int i,int lettre) throws InterruptedException {		
		if(i==0){
			//Thread.sleep(10);
			for (int j = 0; j < lettres.length; j++) {
				s[s.length-1] = lettres[j];
				nbCombi++;
				//print(s);
			}
		}
		else {	
			char[] s2 = s;
			RunAux(s2,i-1,lettre);			
			if(lettre < lettres.length-1) {
				s2[s.length-i-1] = lettres[lettre+1];
				RunAux(s2,i,lettre+1);
			}	
			
		}	
	}
	private void print(char [] s) {
		for (int i = 0; i < s.length; i++) {
			System.out.print((char) chars[i]);
		}
		System.out.println();
	}

	public static void main(String[] args) throws InterruptedException {
		System.out.println("Cas 1 : 6 lettres, alphabet min"); BruteForce cas1= new BruteForce("min", 6);
		
		System.out.println("Cas 2 : 6 lettres, alphabet min et maj"); BruteForce cas2= new BruteForce("min-maj", 6);
		
		System.out.println("Cas 3 : 6 lettres, alphabet min et maj et chiffres"); BruteForce cas3= new BruteForce("min-maj-chiffre", 6);
		
		System.out.println("Cas 4 : 7 lettres, alphabet min"); BruteForce cas4= new BruteForce("min", 7);
		
		System.out.println("Cas 5 : 7 lettres, alphabet min et maj"); BruteForce cas5= new BruteForce("min-maj", 7);
		
		System.out.println("Cas 6 : 7 lettres, alphabet min et maj et chiffres"); BruteForce cas6= new BruteForce("min-maj-chiffre", 7);
		
		System.out.println("Cas 7 : 8 lettres, alphabet min"); BruteForce cas7= new BruteForce("min", 8);
	}

}