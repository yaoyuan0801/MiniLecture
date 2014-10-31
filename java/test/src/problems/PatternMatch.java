package problems;

import java.util.ArrayList;
import java.util.HashMap;

public class PatternMatch {
    public boolean isPatternMatched(String str, String pattern) {
        if (pattern.length() < 1) {
            return true;
        }
        ArrayList<ArrayList<HashMap<Character, String>>> res1 = new ArrayList<ArrayList<HashMap<Character, String>>>(str.length());
        ArrayList<ArrayList<HashMap<Character, String>>> res2 = new ArrayList<ArrayList<HashMap<Character, String>>>(str.length());
        for (int i = 0; i < str.length(); i++) {
            res1.add(i, new ArrayList<HashMap<Character, String>>());
            res2.add(i, new ArrayList<HashMap<Character, String>>());
            HashMap<Character, String> m = new HashMap<Character, String>();
            m.put(pattern.charAt(0), str.substring(0, i + 1));
            res1.get(i).add(m);
        }
        for (int i = 1; i < pattern.length(); i++) {
            for (int j = 0; j < str.length(); j++) {     
                res2.get(j).clear();
                for (int k = 1; k <= j; k++) {
                    String lastWord = str.substring(k, j + 1);
                    for (HashMap<Character, String> m : res1.get(k - 1)) {
                        if (!m.containsKey(pattern.charAt(i))) {
                            HashMap<Character, String> m1 = new HashMap<Character, String>(m);
                            m1.put(pattern.charAt(i), lastWord);
                            res2.get(j).add(m1);
                        } else if (m.get(pattern.charAt(i)).equals(lastWord)) {
                            HashMap<Character, String> m1 = new HashMap<Character, String>(m);
                            res2.get(j).add(m1);
                        }
                    }
                }
            }
            ArrayList<ArrayList<HashMap<Character, String>>> res3 = res1;
            res1 = res2;
            res2 = res3;
        }
        for (HashMap<Character, String> m: res1.get(str.length() - 1)) {
            for (Character key : m.keySet()) {
                System.out.println(key + ":" + m.get(key));
            }
        }
        return res1.get(str.length() - 1).size() > 0;
    }
    public static void main(String[] args) {
        String str= new String("asdasdasdasd"), pattern = new String("AAAA");
        PatternMatch matcher = new PatternMatch();
        System.out.println(matcher.isPatternMatched(str, pattern));
        str = "bigboyboybig";
        pattern = "ABBA";
        System.out.println(matcher.isPatternMatched(str, pattern));
    }

}
