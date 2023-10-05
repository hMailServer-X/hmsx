-- This example shows how a connection to a hMailServer X remote 
-- instance can be done using the LUA Scripting Language
-- Please check also the build instructions at the end of file 


local socket = require("socket")
local ssl = require("ssl")

-- Define host and port
local host = "220.240.130.70"
local port = 9999

-- Create the SSL context and disable certificate verification
local ctx = ssl.newcontext({protocol = "tlsv1"})
ctx:setverify("none")

-- Connect to the server
local sock = socket.tcp()
sock:settimeout(5)
local success, err = sock:connect(host, port)

if success then
    local ssock = ctx:wrap(sock)
    ssock:settimeout(5)

    -- Call get_domains() after successful TLS connection
    print("\nhMailServer API call via LUA\n")
    print("\nDomains\n")
    ssock:send("get_domains()\n")
    local response, err = ssock:receive("*l")
    print(response and response .. "\n" or err)

    -- Call get_startup_time() after successful TLS connection
    ssock:send("get_startup_time()\n")
    local response, err = ssock:receive("*l")
    print(response and response .. "\n" or err)

    ssock:close()
else
    print("Connection error: " .. err)
end

sock:close()


-- Install dependencis like follows:
-- Use for example: "sudo apt install lua5.1-sec-dev" to install lua's ssl features
