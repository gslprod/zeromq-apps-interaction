-module(time_client).
-export([main/0]).

-define(ADDRESS, "/tmp/time_server").
-define(PROTOCOL, ipc). %todo - ipc is not supported (tcp only)

main() ->
    application:start(chumak),
    {ok, Socket} = chumak:socket(sub),
    chumak:subscribe(Socket, <<"">>),

    case chumak:connect(Socket, ?PROTOCOL, ?ADDRESS, 0) of
        ok ->
            io:format("Connected successfully"),
            loop(Socket);
        {error, Reason} ->
            io:format("Connection failed for this reason: ~p~n", [Reason]);
        X ->
            io:format("Unhandled reply for connection: ~p~n", [X])
    end.

loop(Socket) ->
    case chumak:recv(Socket) of
        {ok, TimeData} ->
            io:format("Time received: ~p~n", [TimeData]),
            loop(Socket);
        {error, Reason} ->
            io:format("Receive error: ~p~n", [Reason]);
        X ->
            io:format("Unhandled content received: ~p~n", [X])
    end.
