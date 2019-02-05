import inet.applications.udpapp.UDPBasicApp;

simple myUDPAppDL extends UDPBasicApp
{
    parameters:
        int numConnections=default(2);
    
    @class(myUDPAppDL);
        
}