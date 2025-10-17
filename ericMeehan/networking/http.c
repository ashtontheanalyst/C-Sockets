void launch(struct Server *server) {
    int address_length = sizeof(server->address);
    int new_socket;
    FILE *html;
    char response[4096];
    char buffer[1024];
    
    while (1) {
        printf("----- WAITING FOR CONNECTION -----\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        if (new_socket < 0) {
            perror("accept");
            continue;
        }
        printf("Client Connected\n");

        // --- Read the client's request (optional, just to clear the buffer)
        read(new_socket, buffer, sizeof(buffer) - 1);
        printf("Received request:\n%s\n", buffer);

        // --- Open your HTML file
        html = fopen("index.html", "r");
        if (!html) {
            perror("fopen");
            close(new_socket);
            continue;
        }

        // --- Send HTTP header
        char header[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Connection: close\r\n"
                        "\r\n";
        write(new_socket, header, strlen(header));

        // --- Send the HTML file contents
        char line[1024];
        while (fgets(line, sizeof(line), html)) {
            write(new_socket, line, strlen(line));
        }
        fclose(html);

        printf("Served index.html\n");
        close(new_socket);
        printf("Client Connection Closed...\n\n");
    }
}
