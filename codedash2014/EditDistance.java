import java.io.*;
import java.util.LinkedList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: John
 * Date: 8/10/14
 * Time: 4:30 PM
 * To change this template use File | Settings | File Templates.
 */

class Trie
{
    public final static int MAX_CHILDREN = 26;
    public Trie()
    {
        isWord_ = false;
        children_ = new Trie[MAX_CHILDREN];
    }

    public void insertWord(String word)
    {
        if (word.length() == 0)
        {
            isWord_ = true;
            return;
        }
        int letter = word.charAt(0)-'a';
        if (children_[letter] == null)
        {
            children_[letter] = new Trie();
        }
        children_[letter].insertWord(word.substring(1));
    }

    public boolean contains(String word)
    {
        if (word.length() == 0)
        {
            return isWord_;
        }
        int letter = word.charAt(0)-'a';
        if (children_[letter] != null)
        {
            return children_[letter].contains(word.substring(1));
        }
        return false;
    }

    final Trie[] children_;
    boolean isWord_;
}

public class EditDistance {

    private static int distance_helper(Trie node, char letter, String word, int wordLength, int[] prevRow, int minDist)
    {
        int[] nextRow = new int[wordLength+1];
        nextRow[0] = prevRow[0] + 1;
        int rowMin = Integer.MAX_VALUE;
        for (int i = 0; i < wordLength; ++i)
        {
            int currentCost;
            if (letter == word.charAt(i))
            {
                currentCost = prevRow[i];
            }
            else
            {
                currentCost = Math.min(Math.min(prevRow[i]+1, prevRow[i+1]+1), nextRow[i]+1);
            }
            nextRow[i+1] = currentCost;
            if (currentCost < rowMin)
            {
                rowMin = currentCost;
            }
        }

        if (nextRow[wordLength] < minDist && node.isWord_)
        {
            minDist = nextRow[wordLength];
        }

        if (rowMin < minDist)
        {
            for (int i = 0; i < Trie.MAX_CHILDREN; ++i)
            {
                if (node.children_[i] != null)
                {
                    int dist = distance_helper(node.children_[i], (char)(i+'a'), word, wordLength, nextRow, minDist);
                    if (dist == 1)
                    {
                        return 1;
                    }
                    if (dist < minDist)
                    {
                        minDist = dist;
                    }
                }
            }
        }

        return minDist;
    }

    private static int distance(String word, Trie dict)
    {
        if (dict.contains(word))
        {
            return 0;
        }

        int minDist = Integer.MAX_VALUE;
        int wordLength = word.length();
        int[] row = new int[wordLength+1];
        for (int i = 0; i < wordLength+1; i++)
        {
            row[i] = i;
        }
        for (int i = 0; i < Trie.MAX_CHILDREN; i++)
        {
            if (dict.children_[i] != null)
            {
                int dist = distance_helper(dict.children_[i], (char)(i+'a'), word, wordLength, row, minDist);
                if (dist == 1)
                {
                    return 1;
                }
                else if (dist < minDist)
                {
                    minDist = dist;
                }
            }
        }
        return minDist;
    }

    public static void main(String[] args)
    {
        Trie dict = new Trie();
        List<String> words = new LinkedList<String>();
        try
        {
            //BufferedReader in = new BufferedReader(new FileReader("problem_2008.in"));
            BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
            int num_dict_words = Integer.parseInt(in.readLine());
            for (int i = 0; i < num_dict_words; ++i)
            {
                dict.insertWord(in.readLine());
            }
            int num_words = Integer.parseInt(in.readLine());
            for (int i = 0; i < num_words; ++i)
            {
                words.add(in.readLine());
            }
        }
        catch (FileNotFoundException e)
        {
            e.printStackTrace();
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }

        long startTime = System.currentTimeMillis();
        //int totalDistance = 0;
        StringBuilder output = new StringBuilder();
        for (String word : words)
        {
            int dist = distance(word, dict);
            //totalDistance += dist;
            //System.out.format("%s: %d\n", word, dist);
            //System.out.format("%d\n", dist);
            output.append(dist);
            output.append("\n");
        }
        long endTime = System.currentTimeMillis();

        //System.out.println(totalDistance);
        System.out.print(output.toString());
        System.err.format("took %d ms\n", (endTime-startTime));
    }
}
