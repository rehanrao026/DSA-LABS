#include <iostream>
using namespace std;

// Node structure
struct Player {
    int PlayerID;
    int Score;
    Player* next;
};

class Game {
private:
    Player* tail;
    Player* current;

public:
    Game() {
        tail = NULL;
        current = NULL;
    }

    // 1. Add player
    void addPlayer(int id, int score) {
        Player* newPlayer = new Player{ id, score, NULL };

        if (!tail) {
            tail = newPlayer;
            tail->next = tail;  // circular link
            current = tail;
        }
        else {
            newPlayer->next = tail->next;
            tail->next = newPlayer;
            tail = newPlayer;
        }

        cout << "Player " << id << " joined the game.\n";
    }

    // 2. Remove player
    void removePlayer(int id) {
        if (!tail) return;

        Player* curr = tail->next;
        Player* prev = tail;

        do {
            if (curr->PlayerID == id) {

                // Only one player
                if (curr == tail && curr->next == tail) {
                    cout << "Player " << id << " removed.\n";
                    delete curr;
                    tail = current = NULL;
                    return;
                }

                // Removing tail
                if (curr == tail) {
                    prev->next = curr->next;
                    tail = prev;
                }
                else {
                    prev->next = curr->next;
                }

                // Adjust current pointer
                if (current == curr)
                    current = curr->next;

                cout << "Player " << id << " removed.\n";
                delete curr;
                return;
            }

            prev = curr;
            curr = curr->next;

        } while (curr != tail->next);

        cout << "Player not found!\n";
    }

    // 3. Next turn
    void nextTurn() {
        if (!current) return;
        current = current->next;
        cout << "Player " << current->PlayerID << "'s turn.\n";
    }

    // 4. Skip player
    void skipPlayer() {
        if (!current) return;
        cout << "Player " << current->PlayerID << " is skipped!\n";
        current = current->next; // skip current
        current = current->next; // move to next
        cout << "Now Player " << current->PlayerID << "'s turn.\n";
    }

    // 5. Check winner
    void checkWinner() {
        if (tail && tail == tail->next) {
            cout << "Player " << tail->PlayerID << " wins the game!\n";
        }
    }

    // Display players
    void display() {
        if (!tail) return;

        Player* temp = tail->next;
        cout << "\nPlayers in game:\n";

        do {
            cout << "PlayerID: " << temp->PlayerID
                << ", Score: " << temp->Score << endl;
            temp = temp->next;
        } while (temp != tail->next);
    }
};

// Main
int main() {
    Game g;

    g.addPlayer(1, 10);
    g.addPlayer(2, 20);
    g.addPlayer(3, 15);

    g.display();

    g.nextTurn();
    g.nextTurn();

    g.skipPlayer();

    g.removePlayer(2);
    g.display();

    g.removePlayer(1);
    g.removePlayer(3);

    g.checkWinner();

    return 0;
}