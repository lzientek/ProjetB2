int Get_Request(int conn, struct ReqInfo * reqinfo) {

    char   buffer[MAX_REQ_LINE] = {0};
    int    rval;
    fd_set fds;
    struct timeval tv;


    /*  Set timeout to 5 seconds  */

    tv.tv_sec  = 5;
    tv.tv_usec = 0;


    /*  Loop through request headers. If we have a simple request,
	then we will loop only once. Otherwise, we will loop until
	we receive a blank line which signifies the end of the headers,
	or until select() times out, whichever is sooner.                */

    do {

	/*  Reset file descriptor set  */

	FD_ZERO(&fds);
	FD_SET (conn, &fds);


	/*  Wait until the timeout to see if input is ready  */

	rval = select(conn + 1, &fds, NULL, NULL, &tv);


	/*  Take appropriate action based on return from select()  */

	if ( rval < 0 ) {
	    Error_Quit("Error calling select() in get_request()");
	}
	else if ( rval == 0 ) {

	    /*  input not ready after timeout  */

	    return -1;

	}
	else {

	    /*  We have an input line waiting, so retrieve it  */

	    Readline(conn, buffer, MAX_REQ_LINE - 1);
	    Trim(buffer);

	    if ( buffer[0] == '\0' )
		break;

	    if ( Parse_HTTP_Header(buffer, reqinfo) )
		break;
	}
    } while ( reqinfo->type != SIMPLE );

    return 0;
}

