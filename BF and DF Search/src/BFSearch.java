// BFSearch
// 
// This class is the heart of Breadth First Search algorithm. It takes initial location and 
// final location and then returns a waypoint as a solution, if one exists, otherwise it
// returns a null. Repeated state checking has also been taken care of in this class.
//  
// Abdur Rafay -- Sun 9/28/2014
// 




import java.util.HashSet;
public class BFSearch 
{
	public int expansionCount;
	public int Limit;
	public Map graph;
	public String initialLoc;
	public String destinationLoc;

	public BFSearch(Map graph, String initialLoc, String destinationLoc, int limit) 
	{
		this.Limit = limit;
		this.graph = graph;
		this.initialLoc = initialLoc;
		this.destinationLoc = destinationLoc;	
	}

	public Waypoint search(boolean repeated) 
	{	
		expansionCount = 0;
		
		if (!repeated)
		{
			Frontier frontier = new Frontier ();
			Waypoint wayPoint = new Waypoint(graph.findLocation(initialLoc));
			wayPoint.previous = null;
			
			if (wayPoint.isFinalDestination(destinationLoc))
			{
				return wayPoint;
			}
		
			wayPoint.expand();
			
			while (expansionCount < Limit  && !wayPoint.isFinalDestination(destinationLoc) )
			{	
				for (int j = 0; j < wayPoint.options.size(); j++)
				{
					Waypoint wayPointInLoop = wayPoint.options.get(j);
					wayPointInLoop.previous = wayPoint;
					frontier.addToBottom(wayPointInLoop);
				}	
				
				expansionCount++;
				wayPoint = frontier.removeTop();
				wayPoint.expand();
			}
			
			if (expansionCount == Limit)
				return null;
			
			else
				return wayPoint;
		}
		
		else	
		{	
			Frontier frontier = new Frontier ();
			HashSet<String> explored = new HashSet<String>();
			Waypoint wayPoint = new Waypoint(graph.findLocation(initialLoc));
			wayPoint.previous = null;
			
			if (wayPoint.isFinalDestination(destinationLoc))
			{
				return wayPoint;
			}

			explored.add(wayPoint.loc.name);
			wayPoint.expand();
			expansionCount++;
			
			while (expansionCount < Limit  && !wayPoint.isFinalDestination(destinationLoc) )
			{	
				
				for (int j = 0; j < wayPoint.options.size(); j++)
				{
					Waypoint wayPointInLoop = wayPoint.options.get(j);
					
					if (wayPointInLoop.isFinalDestination(destinationLoc))
					{
						return wayPointInLoop;
					}
					
					if (!frontier.contains(wayPointInLoop.loc.name) && !explored.contains(wayPointInLoop.loc.name))
					{
						wayPointInLoop.previous = wayPoint;
						explored.add(wayPointInLoop.loc.name);
						frontier.addToBottom(wayPointInLoop);
						expansionCount++;
					}
				}
				wayPoint = frontier.removeTop();
				wayPoint.expand();
			}
			return null;
		}
	}

}
