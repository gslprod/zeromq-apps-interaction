-module(time_client).
-export([main/0]).

-define(ADDRESS, "localhost").
-define(PROTOCOL, tcp).
-define(PORT, 5555).

main() ->
    %% creating and setting up SUB socket
    application:start(chumak),
    {ok, Socket} = chumak:socket(sub),
    chumak:subscribe(Socket, <<"">>),

    %% connecting to publisher
    %% start a main loop if successful
    case chumak:connect(Socket, ?PROTOCOL, ?ADDRESS, ?PORT) of
        {ok, _BindPid} ->
            io:format("Connected successfully"),
            loop(Socket);
        {error, Reason} ->
            io:format("Connection failed for this reason: ~p~n", [Reason]);
        X ->
            io:format("Unhandled reply for connection: ~p~n", [X])
    end.

%% main loop - receiving and printing data
loop(Socket) ->
    case chumak:recv(Socket) of
        {ok, TimeData} ->
            io:format("Time received: ~p~n", [TimeData]),
            loop(Socket);
        {error, Reason} ->
            io:format("Receive error: ~p~n", [Reason])
    end.
