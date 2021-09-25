cmake_minimum_required(VERSION 3.20)
project(Project1_Starter_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1_Starter_Code
        Automaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h MatcherAutomaton.cpp MatcherAutomaton.h StringAutomaton.cpp StringAutomaton.h IdAutomaton.cpp IdAutomaton.h LineCommentAutomaton.cpp LineCommentAutomaton.h IncompleteStringAutomaton.cpp IncompleteStringAutomaton.h BlockCommentAutomaton.cpp BlockCommentAutomaton.h InvalidBlockCommentAutomaton.cpp InvalidBlockCommentAutomaton.h Parser.cpp Parser.h DatalogProgram.cpp DatalogProgram.h Predicate.cpp Predicate.h Rule.cpp Rule.h Parameter.cpp Parameter.h)
