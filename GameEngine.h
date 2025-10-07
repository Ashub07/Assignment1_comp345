#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"

/**
 *
 * The possible state that the game engine can be in.
 */
enum class GameState {
    Start,             ///< Initial state before any game
    MapLoaded,         ///< Map data has been loaded
    MapValidated,      ///< Loaded map has been validated
    PlayersAdded,      ///< At least one player has been added
    AssignReinforcement,///< Start of the game
    IssueOrders,       ///< Players orders are issued
    ExecuteOrders,     ///< Players orders are executed
    Win,               ///< A player wins
    End                ///< End of the game
};

/**
 *
 * The game engine takes a command string as input and updates
 * the current state when a valid transition exists. Commands 
 * with no valid transition from the current state are rejected.
 *
 * Example usage:
 *   GameEngine g;
 *   g.processCommand("loadmap");       // Start -> MapLoaded
 *   g.processCommand("validatemap");   // MapLoaded -> MapValidated
 *   g.processCommand("addplayer");     // MapValidated -> PlayersAdded
 */
class GameEngine {
public:
    GameEngine();

    /**
     * Return the current state value.
     */
    GameState state() const noexcept { return state_; }

    /**
     * Return the current state as a human-readable string.
     */
    std::string stateName() const;

    /**
     * Attempt to apply a command to the current state.
     *
     * @param command Command string
     * @return true if a valid transition exists; false if rejected.
     */
    bool processCommand(const std::string& command);

    /**
     * Show the possible commands from the current state.
     *
     * @return A list of command strings that are accepted in the current state.
     */
    std::vector<std::string> availableCommands() const;

private:
    // --- Game Engine Core ---
    GameState state_;
    std::unordered_map<GameState, std::unordered_map<std::string, GameState>> transitions_;
    static std::string toLower(std::string s);
    static std::string trim(const std::string& s);
    void buildTransitions();

    // --- Integrating Parts 1–4 ---
    MapLoader loader_;                 // Map loader 
    Map* map_{nullptr};                // Active map
    std::vector<Player*> players_;     // Owned here
    Deck deck_;                        // Shared deck

    // --- Hooks for each command ---
    void onLoadMap();          // start -> map loaded
    void onValidateMap();      // map loaded -> map validated
    void onAddPlayer();        // map validated -> players added
    void onAssignCountries();  // players added -> assign reinforcement
    void onIssueOrder();       // assign reinforcement -> issue orders
    void onEndIssueOrders();   // issue orders -> execute orders
    void onEndExecOrders();    // execute orders -> assign reinforcement
    void onWin();              // execute orders -> win
    void onPlayAgain();        // win -> assign reinforcement
    void onEnd();              // win -> end

    // --- Utilities ---
    void distributeRoundRobin();     // territory assignment
    void clearPlayers();             // deletes owned Player*
};

#endif // GAME_ENGINE_H
