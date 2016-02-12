// A*Search
// 
// This class implements A* Search algorithm which takes an initial location and
// a final location and returns a solution, if one exists, else a null.
// 
// Abdur Rafay -- Sun 10/12/2014
// 
//

import java.util.HashSet;
public class AStarSearch 
{
	public int expansionCount;
	public int Limit;
	public Map graph;
	public String initialLoc;
	public String destinationLoc;

	public AStarSearch(Map graph, String initialLoc, String destinationLoc, int limit) 
	{
		this.Limit = limit;
		this.graph = graph;
		this.initialLoc = initialLoc;
		this.destinationLoc = destinationLoc;
	}

	public Waypoint search(boolean repeated) 
	{	
		expansionCount = 0;
		SortedFrontier frontier = new SortedFrontier (SortBy.f);
		Waypoint wayPoint = new Waypoint(graph.findLocation(initialLoc));
		GoodHeuristic h = new GoodHeuristic (graph.findLocation(destinationLoc),graph);
		
		if (wayPoint.isFinalDestination(destinationLoc)) 
			return wayPoint;
		
		wayPoint.expand(h);
		
		if (!repeated)	
		{
			while (wayPoint.depth < Limit)
			{	
				expansionCount++;
				
				for (int i = 0; i <wayPoint.options.size(); i++)
				{
					frontier.addSorted(wayPoint.options.get(i));
				}
				
				if (frontier.isEmpty()) 
					return null;
				
				wayPoint = frontier.removeTop();
				
				if (wayPoint.isFinalDestination(destinationLoc)) 
					return wayPoint;
				
				wayPoint.expand(h);
			}
		}
		
		else	
		{	
			HashSet<String> explored = new HashSet<String>();
			explored.add(wayPoint.loc.name);
			
			while (wayPoint.depth < Limit)
			{	
				expansionCount++;
				
				for (int i = 0; i < wayPoint.options.size(); i++)
				{
					Waypoint wayPointInLoop = wayPoint.options.get(i);
					if (!frontier.contains(wayPointInLoop.loc.name) && !explored.contains(wayPointInLoop.loc.name))
					{
						explored.add(wayPointInLoop.loc.name);
						frontier.addSorted(wayPointInLoop);
						
					}
					 
					else if (frontier.contains(wayPointInLoop.loc.name))
					{	
						Waypoint wPartial = frontier.find(wayPointInLoop.loc.name);
						if (wayPointInLoop.partialPathCost < wPartial.partialPathCost)
						{
							frontier.remove(wPartial);
							frontier.addSorted(wayPointInLoop);
						}
					}
				}
				
				if (frontier.isEmpty()) 
					return null;
				
				wayPoint = frontier.removeTop();
				
				if (wayPoint.isFinalDestination(destinationLoc)) 
					return wayPoint;
				
				wayPoint.expand(h);
			}
		}
		
		if (wayPoint.depth == Limit)
			return null;
		
		else
			return wayPoint;
	}

}
