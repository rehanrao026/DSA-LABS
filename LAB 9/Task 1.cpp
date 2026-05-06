#include <iostream>
using namespace std;

// Node structure
struct Song {
    int SongID;
    string SongName;
    float Duration;
    Song* next;
    Song* prev;
};

// Playlist class
class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = tail = current = NULL;
    }

    // 1. Add song at end
    void addSong(int id, string name, float duration) {
        Song* newSong = new Song{ id, name, duration, NULL, NULL };

        if (!head) {
            head = tail = current = newSong;
        }
        else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song added: " << name << endl;
    }

    // 2. Delete song by name
    void deleteSong(string name) {
        Song* temp = head;

        while (temp) {
            if (temp->SongName == name) {

                // If node is head
                if (temp == head) {
                    head = head->next;
                    if (head) head->prev = NULL;
                }
                // If node is tail
                else if (temp == tail) {
                    tail = tail->prev;
                    tail->next = NULL;
                }
                // Middle node
                else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }

                // Adjust current pointer
                if (current == temp)
                    current = temp->next ? temp->next : temp->prev;

                delete temp;
                cout << "Song deleted: " << name << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!" << endl;
    }

    // 3. Play next
    void playNext() {
        if (current && current->next) {
            current = current->next;
            cout << "Now playing: " << current->SongName << endl;
        }
        else {
            cout << "No next song available!" << endl;
        }
    }

    // Play previous
    void playPrevious() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Now playing: " << current->SongName << endl;
        }
        else {
            cout << "No previous song available!" << endl;
        }
    }

    // 4. Reverse playlist
    void reversePlaylist() {
        Song* temp = NULL;
        Song* curr = head;

        while (curr) {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }

        if (temp)
            head = temp->prev;

        cout << "Playlist reversed!" << endl;
    }

    // 5. Display playlist
    void display() {
        Song* temp = head;
        cout << "\nPlaylist:\n";
        while (temp) {
            cout << "ID: " << temp->SongID
                << ", Name: " << temp->SongName
                << ", Duration: " << temp->Duration << " mins\n";
            temp = temp->next;
        }
    }
};

// Main function
int main() {
    Playlist p;

    p.addSong(1, "Song A", 3.5);
    p.addSong(2, "Song B", 4.0);
    p.addSong(3, "Song C", 2.8);

    p.display();

    p.playNext();
    p.playNext();
    p.playPrevious();

    p.deleteSong("Song B");
    p.display();

    p.reversePlaylist();
    p.display();

    return 0;
}