#include "ladder.h"
#include <cstddef>
#include <fstream>
#include <vector>
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void error(string word1, string word2, string msg){
    msg = word1 + word2;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d){
    if(str1 == str2){
        return true;
    }
    int str1_len = str1.length();
    int str2_len = str2.length();
    if(str1_len - str2_len > 1 || str1_len - str2_len < -1){
        return false;
    }

    int edits = 0; 

    for (int i = 0, j = 0; i < str1_len || j < str2_len;) {
        if (i < str1_len && j < str2_len && str1[i] == str2[j]) {
            ++i; 
            ++j;
        }else{
            ++edits;
            if(edits > d){
                return false;
            }
            if(str1_len > str2_len){++i;}
            else if (str1_len < str2_len) {++j;}
            else{
                ++i; 
                ++j;
            }
        }
    }
    return edits <= d;
}

bool is_adjacent(const string &word1, const string &word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited_set;
    visited_set.insert(begin_word);

    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        string last_word = ladder.back();
        ladder_queue.pop();

        for(const string&word: word_list){
            if(is_adjacent(last_word, word)){
                if(visited_set.find(word) == visited_set.end()){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    visited_set.insert(word);
                    if(word == end_word){
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> &word_list, const string &file_name){
    ifstream in(file_name);
    for(string word; in >>word;){
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string> &ladder){
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for(size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i];
        if(i != ladder.size() -1){
            cout << " ";
        }
    }
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "word.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}