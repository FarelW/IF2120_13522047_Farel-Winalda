def dijkstra(graph, start, end):
    shortest_paths = {start: (None, 0)}
    visited = set()
    current_node = start

    while current_node != end:
        visited.add(current_node)
        destinations = graph[current_node]
        weight_to_current = shortest_paths[current_node][1]

        for next_node, weight in destinations.items():
            new_weight = weight + weight_to_current
            if new_weight < shortest_paths.get(next_node, (None, float('inf')))[1]:
                shortest_paths[next_node] = (current_node, new_weight)
        
        next_destinations = {node: shortest_paths[node] for node in shortest_paths if node not in visited}
        if not next_destinations:
            return "Route Not Possible"
        
        print(f"Current Node: {current_node}, Next Destinations: {next_destinations}")
        
        current_node = min(next_destinations, key=lambda k: next_destinations[k][1])

    path = []
    while current_node:
        path.append(current_node)
        current_node = shortest_paths[current_node][0]
        
    print(f"Final Path: {path}")
    return path[::-1]