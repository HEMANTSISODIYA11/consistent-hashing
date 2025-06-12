#include <bits/stdc++.h>
using namespace std;

class CacheNode{
public:
    map<string, string> keyToValueMap;
    
    CacheNode() {
        this->keyToValueMap = {};
    }
};

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

long long generateHash(string key) {
    
    return static_cast<long long>(std::hash<std::string>{}(key));
}

void addNode(
    string nodeId, 
    map<string, CacheNode*> &nodeIdToCacheNodeMapping, 
    set<long long> &nodeIdsHash, 
    map<long long, string> &hashToNodeIdMap
) {
    
    long long nodeHash = generateHash(nodeId);
    cout<<nodeHash<<endl;
    CacheNode* node = new CacheNode();
    
    nodeIdToCacheNodeMapping[nodeId] = node;
    nodeIdsHash.insert(nodeHash);
    hashToNodeIdMap[nodeHash] = nodeId;
}

void deleteNode(
    string nodeId,
    map<string, CacheNode*> &nodeIdToCacheNodeMapping, 
    set<long long> &nodeIdsHash, 
    map<long long, string> &hashToNodeIdMap
) {
    
    long long nodeHash = generateHash(nodeId);
    cout<<nodeHash<<endl;
    nodeIdToCacheNodeMapping.erase(nodeId);
    nodeIdsHash.erase(nodeHash);
    hashToNodeIdMap.erase(nodeHash);
}

void addKey(
    string key,
    string value,
    map<string, CacheNode*> &nodeIdToCacheNodeMapping, 
    set<long long> &nodeIdsHash, 
    map<long long, string> &hashToNodeIdMap,
    map<string, string> &actualDatabase
) {
    
    actualDatabase[key] = value;
    long long keyHash = generateHash(key);
    auto nodeHashPtr = nodeIdsHash.lower_bound(keyHash);
    
    if(nodeHashPtr == nodeIdsHash.end()) {
        nodeHashPtr == nodeIdsHash.begin();
    }
    
    long long selectedNodeHash = *nodeHashPtr;
    string selectedNodeId = hashToNodeIdMap[selectedNodeHash];
    CacheNode* node = nodeIdToCacheNodeMapping[selectedNodeId];
    
    node->keyToValueMap[key] = value;
    cout<<"inserted value in node: "<<selectedNodeId<<",for key: "<<key<<endl;
}

string getKey(
    string key,
    map<string, CacheNode*> &nodeIdToCacheNodeMapping, 
    set<long long> &nodeIdsHash, 
    map<long long, string> &hashToNodeIdMap,
    map<string, string> &actualDatabase
) {
    
    long long keyHash = generateHash(key);
    
    auto nodeHashPtr = nodeIdsHash.lower_bound(keyHash);
    
    for(auto itr : nodeIdsHash) {
        cout<<itr<<endl;
    }
    
    if(nodeHashPtr == nodeIdsHash.end()) {
        nodeHashPtr = nodeIdsHash.begin();
    }
    cout<<*nodeHashPtr<<endl;
    
    long long selectedNodeHash = *nodeHashPtr;
    string selectedNodeId = hashToNodeIdMap[selectedNodeHash];
    CacheNode* node = nodeIdToCacheNodeMapping[selectedNodeId];
    
    if(node->keyToValueMap.count(key) > 0) {
        cout<<"value is found in hash"<<endl;
        return node->keyToValueMap[key];
    }
    
    
    if(actualDatabase.count(key) > 0) {
        cout<<"value is found in database"<<endl;
        node->keyToValueMap[key] = actualDatabase[key];
        return node->keyToValueMap[key];
    }
    
    cout<<"value could not be found in database"<<endl;
    return "-1";
}


int main() {

    string userInput;
    
    map<long long, string> hashToNodeIdMap;
    map<string, string> actualDatabase;
    map<string, CacheNode*> nodeIdToCacheNodeMapping;
    set<long long> nodeIdsHash;
    
    while (true) {
        std::cout << "\nEnter your command or message: ";
        std::getline(std::cin, userInput);

        std::string lowerCaseInput = userInput;
        
        std::cout << "\nUser entered: ";
        
        vector<string> parts = split(lowerCaseInput, ',');
        
        if(parts.size() == 0) {
            break;
        }
        
        
        if(parts[0] == "exit") {
            break;
        }
        
        if(parts[0] == "addnode") {
            
            addNode(
                parts[1], 
                nodeIdToCacheNodeMapping, 
                nodeIdsHash, 
                hashToNodeIdMap
            );
        }
        
        if(parts[0] == "delnode") {
            
            deleteNode(
                parts[1],
                nodeIdToCacheNodeMapping, 
                nodeIdsHash, 
                hashToNodeIdMap
            );
        }
        
        if(parts[0] == "getkey") {
            string value = getKey(
                parts[1],
                nodeIdToCacheNodeMapping, 
                nodeIdsHash, 
                hashToNodeIdMap,
                actualDatabase
            );
            
            cout<<"value for key is :"<<value<<endl;
        }
        
        if(parts[0] == "addkey") {
            
            addKey(
                parts[1],
                parts[2],
                nodeIdToCacheNodeMapping, 
                nodeIdsHash, 
                hashToNodeIdMap,
                actualDatabase
            );
        }
        
    }

    return 0;
}

