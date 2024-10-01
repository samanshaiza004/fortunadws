# FortunaDWS

FortunaDWS is a custom web server built from scratch in C++ with a focus on high-performance, event-driven, asynchronous I/O. The project is designed to handle multiple client connections simultaneously while maintaining a responsive and efficient architecture. By leveraging non-blocking I/O and event loops, the server aims to provide a scalable and robust foundation for web services.

This project is a demonstration of deep C++ skills and asynchronous programming, which are essential for building high-performance systems, particularly in distributed environments. Future iterations will introduce features like distributed workloads across multiple nodes, session management, and security enhancements such as SSL/TLS.

## Features (so far)

- _Asynchronouse I/O_: the server utilizes Boost.Asio to manage client connections asynchronously, allowing multiple clients to interact with the server simultaneously without blocking.

- _HTTP Request Parsing_: Simple parsing of incoming HTTP requests (currently handling GET requests).

- _HTTP Response Handling_: Sending basic HTTP responses, including HTML content.

## Features to come

- Improved Request Parsing: Extend the request parsing functionality to handle more complex HTTP methods (POST, PUT, etc.), query parameters, headers, and form data.

- Session Management: Implement session handling to track users across multiple connections. This will be crucial when the server is scaled across distributed nodes.

- SSL/TLS Support: Enhance the security of the server by adding support for SSL/TLS to ensure secure communication between clients and the server.

- Load Balancing: Develop the capability to distribute the workload across multiple nodes, leveraging a load balancer to achieve horizontal scalability. This will allow FortunaDWS to handle much higher traffic loads by spreading client connections across several servers.

- Distributed Session Handling: As the server will be distributed across multiple nodes, implement a mechanism to maintain consistent sessions for clients, regardless of which node they are interacting with.

## License

This project is open-source and available under the MIT [License](LICENSE)
