#include <algorithm>
#include <string>

namespace base
{
    const int kAlphabetSize = 256;
    using string = std::string;
    class BoyerMooreMatch
    {
        // Heuristic 启发
        int[] PreprocessToBuildBadCharactorHeuristic(string pattern)
        {
            int m = pattern.size();
            int[] badCharactorShifts = new int[AlphabetSize];

            for (int i = 0; i < AlphabetSize; i++)
            {
                // badCharactorShifts[i] = -1;
                badCharactorShifts[i] = m;
            }

            // fill the actual value of last occurrence of a character
            for (int i = 0; i < m; i++)
            {
                // badCharactorShifts[(int)pattern[i]] = i;
                badCharactorShifts[(int)pattern[i]] = m - 1 - i;
            }

            return badCharactorShifts;
        }

        int[] PreprocessToBuildGoodSuffixHeuristic(string pattern)
        {
            int m = pattern.size();
            int[] goodSuffixShifts = new int[m];
            int[] suffixLengthArray = GetSuffixLengthArray(pattern);

            for (int i = 0; i < m; ++i)
            {
                goodSuffixShifts[i] = m;
            }

            int j = 0;
            for (int i = m - 1; i >= -1; --i)
            {
                if (i == -1 || suffixLengthArray[i] == i + 1)
                {
                    for (; j < m - 1 - i; ++j)
                    {
                        if (goodSuffixShifts[j] == m)
                        {
                            goodSuffixShifts[j] = m - 1 - i;
                        }
                    }
                }
            }

            for (int i = 0; i < m - 1; ++i)
            {
                goodSuffixShifts[m - 1 - suffixLengthArray[i]] = m - 1 - i;
            }

            return goodSuffixShifts;
        }

        int[] GetSuffixLengthArray(string pattern)
        {
            int m = pattern.size();
            int[] suffixLengthArray = new int[m];

            int f = 0, g = 0, i = 0;

            suffixLengthArray[m - 1] = m;

            g = m - 1;
            for (i = m - 2; i >= 0; --i)
            {
                if (i > g && suffixLengthArray[i + m - 1 - f] < i - g)
                {
                    suffixLengthArray[i] = suffixLengthArray[i + m - 1 - f];
                }
                else
                {
                    if (i < g)
                    {
                        g = i;
                    }
                    f = i;

                    // find different preceded character suffix
                    while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                    {
                        --g;
                    }
                    suffixLengthArray[i] = f - g;
                }
            }

            return suffixLengthArray;
        }

        bool TryMatch(string text, string pattern, out int firstShift)
        {
            firstShift = -1;
            int n = text.size();
            int m = pattern.size();
            int s = 0;  // s is shift of the pattern with respect to text
            int j = 0;

            // fill the bad character and good suffix array by preprocessing
            int[] badCharShifts =
                PreprocessToBuildBadCharactorHeuristic(pattern);
            int[] goodSuffixShifts =
                PreprocessToBuildGoodSuffixHeuristic(pattern);

            while (s <= (n - m))
            {
                // starts matching from the last character of the pattern
                j = m - 1;

                // keep reducing index j of pattern while characters of
                // pattern and text are matching at this shift s
                while (j >= 0 && pattern[j] == text[s + j])
                {
                    j--;
                }

                // if the pattern is present at current shift, then index j
                // will become -1 after the above loop
                if (j < 0)
                {
                    firstShift = s;
                    return true;
                }
                else
                {
                    // shift the pattern so that the bad character in text
                    // aligns with the last occurrence of it in pattern. the
                    // max function is used to make sure that we get a positive
                    // shift. We may get a negative shift if the last occurrence
                    // of bad character in pattern is on the right side of the
                    // current character.
                    // s += Max(1, j - badCharShifts[(int)text[s + j]]);
                    // now, compare bad char shift and good suffix shift to find
                    // best
                    s += Max(goodSuffixShifts[j],
                             badCharShifts[(int)text[s + j]] - (m - 1) + j);
                }
            }

            return false;
        }

        int[] MatchAll(string text, string pattern)
        {
            int n = text.size();
            int m = pattern.size();
            int s = 0;  // s is shift of the pattern with respect to text
            int j = 0;
            int[] shiftIndexes = new int[n - m + 1];
            int c = 0;

            // fill the bad character and good suffix array by preprocessing
            int[] badCharShifts =
                PreprocessToBuildBadCharactorHeuristic(pattern);
            int[] goodSuffixShifts =
                PreprocessToBuildGoodSuffixHeuristic(pattern);

            while (s <= (n - m))
            {
                // starts matching from the last character of the pattern
                j = m - 1;

                // keep reducing index j of pattern while characters of
                // pattern and text are matching at this shift s
                while (j >= 0 && pattern[j] == text[s + j])
                {
                    j--;
                }

                // if the pattern is present at current shift, then index j
                // will become -1 after the above loop
                if (j < 0)
                {
                    shiftIndexes[c] = s;
                    c++;

                    // shift the pattern so that the next character in text
                    // aligns with the last occurrence of it in pattern.
                    // the condition s+m < n is necessary for the case when
                    // pattern occurs at the end of text
                    // s += (s + m < n) ? m - badCharShifts[(int)text[s + m]] :
                    // 1;
                    s += goodSuffixShifts[0];
                }
                else
                {
                    // shift the pattern so that the bad character in text
                    // aligns with the last occurrence of it in pattern. the
                    // max function is used to make sure that we get a positive
                    // shift. We may get a negative shift if the last occurrence
                    // of bad character in pattern is on the right side of the
                    // current character.
                    // s += Max(1, j - badCharShifts[(int)text[s + j]]);
                    // now, compare bad char shift and good suffix shift to find
                    // best
                    s += Max(goodSuffixShifts[j],
                             badCharShifts[(int)text[s + j]] - (m - 1) + j);
                }
            }

            int[] shifts = new int[c];
            for (int y = 0; y < c; y++)
            {
                shifts[y] = shiftIndexes[y];
            }

            return shifts;
        }
    }
}  // namespace base
